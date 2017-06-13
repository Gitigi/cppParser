#include "ast.hpp"
#include <iostream>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <exception>

using std::cout;
using std::endl;

namespace cpp{namespace ast{
    
    struct printDirective
    {
        void operator()(const directive &value)
        {
            cout<<"#";
            boost::apply_visitor(*this,value);
        }
        void operator()(const define_dir &value)
        {
            cout<<"define "<<value.identifier;
            if(value.params.size() > 0)
            {
                cout<<"(";
                for(auto const &i : value.params)
                {
                    cout<<i<<",";
                }
                cout<<")";
            }
            cout<<" "<<value.defn;
        }
        
        void operator()(const include_dir &value)
        {
            cout<<"include "<<value.file_loc;
        }
        
        void operator()(const std::string &value)
        {
            cout<<value;
        }
    };
    
	struct printExpression
	{
		void operator()(const string &value){
			cout<<value.str;
		}
		void operator()(const symbol &value){
			cout<<value.str;
		}
		
		void operator()(const identifier &value)
		{
			cout<<value.scopeOperator;
			for(const auto &i : value.names){
				cout<<i.name;
				
				if(i.template_params.size() > 0)
				{
					cout<<"<";
					for(auto const &p : i.template_params)
					{
						//(*this)(p);
						try{
							auto expr = boost::get<expression>(p);
							(*this)(expr);
						}
						catch(std::exception &){
							
							
						}
						cout<<",";
					}
					cout<<">";
				}
				
				cout<<"::";
			}
		}
		
		void operator()(const double value){
			cout<<value;
		}
		void operator()(const signed_ &value){
			if(value.sign == "+++" || value.sign == "---")
			{
				boost::apply_visitor(*this,value.operand_);
				cout<<value.sign.substr(0,2);
			}
			else
			{
				cout<<value.sign;
				boost::apply_visitor(*this,value.operand_);
			}
		}
		void operator()(const expression &value){
			boost::apply_visitor(*this,value.first);
			for(const auto &i : value.rest){
				cout<<" ";
				cout<<i.operator_;
				cout<<" ";
				boost::apply_visitor(*this,i.operand_);
				if(i.operator_ == "(")
				{
					cout<<')';
				}
				else if(i.operator_ == "[")
				{
					cout<<']';
				}
			}
		}
		void operator()(const operand &value)
		{
			boost::apply_visitor(*this,value);
		}
		
		void operator()(const argument &value)
		{
			
			for(const auto &i : value.params)
			{
				(*this)(i);
				cout<<",";
			}
			
		}
		
		void operator()(const triExpression &value)
		{
			boost::apply_visitor(*this,value.first);
			for(const auto &i : value.rest)
			{
				cout<<i.firstOperator;
				(*this)(i.firstOperand);
				cout<<i.secondOperator;
				(*this)(i.secondOperand);
			}
		}
		
		void operator()(const Null &value)
		{
			cout<<"Null";
		}
		
		void operator()(const new_expr &value)
		{
			cout<<"new ";
			//(*this)(value.expr);
		}
		
		void operator()(const c_cast &value)
		{
			cout<<"(";
			(*this)(value.type);
			cout<<")";
			(*this)(value.expr);
		}
        
        void operator()(const aggregate &value)
        {
            cout<<"{ ";
            for(auto const &i : value.item)
            {
                boost::apply_visitor(*this,i);
                cout<<",";
            }
            cout<<"}";
        }
		
	};
	
	struct printStatement
	{
        void operator()(const Null &value)
        {
            cout<<"Null";
        }
        
        void operator()(const directive &value)
        {
            printDirective()(value);
        }
        
		void operator()(const expression &value)
		{
			printExpression()(value);
		}
        
        void operator()(const std::list<expression> &value)
        {
            for(auto const &i : value)
            {
                (*this)(i);
            }
        }
        
        void operator()(const std::list<statement> &value)
        {
            for(auto const &i : value)
            {
                (*this)(i);
            }
        }
		
		void operator()(const declarator_ptr &value)
		{
			if(value.member.names.size() > 0)
			{
				printExpression()(value.member);
				cout<<"::";
			}
			for(const auto &i : value.pointers)
			{
				cout<<"*";
			}
			(*this)(value.decl);
		}
		
		void operator()(const declarator_lref &value)
		{
			cout<<"&";
			(*this)(value.decl);
		}
		
		void operator()(const declarator_rref &value)
		{
			cout<<"&&";
			(*this)(value.decl);
		}
		
		void operator()(const declarator_pack &value)
		{
			cout<<"...";
			(*this)(value.decl);
		}
		
		void operator()(const declarator_noptr &value)
		{
			try
			{
				printExpression()(boost::get<identifier>(value));
			}
			catch(std::exception &)
			{
				cout<<"(";
				boost::apply_visitor(*this,boost::get<declarator>(value));
				cout<<")";
			}
		}
		
		void operator()(const declarator_function &value)
		{
			cout<<" function";
		}
		
		void operator()(const declarator_array &value)
		{
			cout<<" array";
		}
		
		void operator()(const declarator_comp &value)
		{
			(*this)(value.base);
			if(value.func_array){
				try
				{
					(*this)(boost::get<declarator_function>(*value.func_array));
				}
				catch(std::exception& )
				{
					(*this)(boost::get<declarator_array>(*value.func_array));
				}
			}
		}
		
		void operator()(const declarator &value)
		{
			boost::apply_visitor(*this,value);
		}
		
		void operator()(const declarator_init &value)
		{
            if(const expression *expr = boost::get<expression>(&value))
            {
                cout<<" = ";
				(*this)(*expr);
            }
			else if(const argument *arg = boost::get<argument>(&value))
            {
                cout<<"(";
                printExpression()(*arg);
                cout<<")";
            }
            else if(const aggregate *agg = boost::get<aggregate>(&value))
            {
                cout<<" = ";
                printExpression()(*agg);
            }
		}
		
		void operator()(const declarator_initializer &value)
		{
			(*this)(value.decl);
			if(value.init)
			{
				(*this)(*value.init);
			}
			
		}
		void operator()(const variable_declaration &value)
		{
			for(const auto &s : value.spec)
			{
				cout<<s<<" ";
			}
			printExpression()(value.type);
			cout<<" ";
			for(const auto &i : value.decl)
			{
				(*this)(i);
				cout<<" , ";
			}
		}
		
		void operator()(const parameter &value)
		{
			cout<<"parameter";
		}
		
		void operator()(const statement &value)
		{
			boost::apply_visitor(*this,value);
		}
		
		void operator()(const std::vector<statement> &value)
		{
			for(auto const &i : value){
				(*this)(i);
				cout<<endl;
			}
		}
		
		void operator()(const terminated_stat &value)
		{
			boost::apply_visitor(*this,value);
			cout<<";";
		}
		
		void operator()(const nonterminated_stat &value)
		{
			boost::apply_visitor(*this,value);
		}
		
		void operator()(const block_stat &value)
		{
			cout<<"{"<<endl;
			for(auto const &i : value.stat){
				(*this)(i);
				cout<<endl;
			}
			cout<<"}";
		}
		
		void operator()(const if_stat &value)
		{
			cout<<"if (";
			boost::apply_visitor(*this,value.condition);
			cout<<")"<<endl;
			(*this)(value.stat);
			cout<<endl;
			for(const auto &i : value.else_if){
				cout<<"else if (";
				boost::apply_visitor(*this,value.condition);
				cout<<")"<<endl;
				(*this)(value.stat);
			}
			cout<<endl;
			if(value.else_)
			{
				cout<<"else"<<endl;
				(*this)(*value.else_);
			}
		}
		
		void operator()(const null_stat &value)
		{
			cout<<";";
		}
		
		void operator()(const try_stat &value)
		{
			cout<<"try"<<endl;
			(*this)(value.stat);
			
			for(const auto &i : value.catch_)
			{
				cout<<"catch(";
				try{
					auto &var = boost::get<parameter>(i.exception_);
					(*this)(var);
				}
				catch(std::exception &)
				{
					cout<<"...";
				}
				cout<<")";
				(*this)(i.stat);
			}
		}
        
        void operator()(const function &value)
        {
            for(const auto &s : value.decl.spec)
			{
				cout<<s<<" ";
			}
			printExpression()(value.decl.type);
            cout<<" ";
            (*this)(value.decl.name);
            (*this)(value.decl.params);
            
            if(boost::get<x3::forward_ast<statements>>(&value.defn))
            {
                cout<<endl<<"{"<<endl;
                (*this)(boost::get<x3::forward_ast<statements>>(value.defn));
                cout<<"}"<<endl;
            }
            else if(boost::get<try_stat>(&value.defn))
            {
                (*this)(boost::get<try_stat>(value.defn));
            }
            else if(boost::get<std::string>(&value.defn))
            {
                cout<<" = "<<boost::get<std::string>(value.defn)<<";"<<endl;
            }
            
        }
        
        void operator()(const class_decl &value)
        {
            cout<<"class declaration";
        }
        
        void operator()(const enum_defn &value)
        {
            cout<<"enum "<<value.nested<<" ";
            if(!value.type.empty()){
                cout<<": "<<value.type;
            }
            cout<<"{ ";
            for(auto const &i : value.enumerators)
            {
                cout<<i.item<<" ";
                if(!i.isSet.empty()){
                    cout<<"=";
                    printExpression()(i.value);
                }
                cout<<", ";
            }
            cout<<"}";
        }
        
        void operator()(const switch_expr &value)
        {
            cout<<"switch(";
            (*this)(value.test);
            cout<<")\n{\n";
            
            for(auto const &i : value.cases){
                if(const switch_case *item = boost::get<switch_case>(&i))
                {
                    cout<<"case ";
                    (*this)(item->condition);
                    cout<<":\n";
                    (*this)(item->action);
                    cout<<endl;
                }
                else
                {
                    cout<<"default:\n";
                    (*this)(boost::get<statements>(i));
                }
            }
            cout<<"}";
        }
        
        void operator()(const for_stat &value)
        {
            cout<<"for(";
            if(const for_loop *loop = boost::get<for_loop>(&value.conditioning)){
                boost::apply_visitor(*this,loop->init);
                cout<<";";
                boost::apply_visitor(*this,loop->condition);
                cout<<";";
                (*this)(loop->iteration);
            }
            else
            {
                const for_range &range = boost::get<for_range>(value.conditioning);
                boost::apply_visitor(*this,range.init);
                cout<<":";
                (*this)(range.iteration);
            }
            cout<<")"<<endl;
            (*this)(value.action);
        }
        
        void operator()(const while_stat &value)
        {
            cout<<"while(";
            boost::apply_visitor(*this,value.condition);
            cout<<")"<<endl;
            (*this)(value.action);
        }
        
        void operator()(const do_stat &value)
        {
            cout<<"do"<<endl;
            (*this)(value.action);
            cout<<"while(";
            (*this)(value.condition);
            cout<<")";
        }
        
        void operator()(const namespace_stat &value)
        {
            cout<<"namespace ";
            boost::apply_visitor(*this,value);
        }
        
        void operator()(const namespace_decl &value)
        {
            printExpression()(value.name);
            cout<<" {"<<endl;
            (*this)(value.decl);
            cout<<"}";
        }
        
        void operator()(const namespace_alias &value)
        {
            cout<<value.alias<<" = ";
            printExpression()(value.value);
            cout<<";";
        }
        
        void operator()(const using_stat &value)
        {
            cout<<"using ";
            if(const using_directive *dir = boost::get<using_directive>(&value))
            {
                cout<<"namespace ";
                printExpression()(dir->ns_name);
            }
            else if(const using_declaration *dec = boost::get<using_declaration>(&value))
            {
                printExpression()(dec->name);
            }
            else if(const using_alias *ali = boost::get<using_alias>(&value))
            {
                cout<<ali->alias<<" = ";
                printExpression()(ali->value);
            }
        }
		
	};
}}