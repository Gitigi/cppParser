#include "ast.hpp"
#include <iostream>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <exception>

using std::cout;
using std::endl;

namespace cpp{namespace ast{
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
		
	};
	
	struct printStatement
	{
		void operator()(const expression &value)
		{
			printExpression()(value);
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
				cout<<boost::get<std::string>(value);
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
			try{
				auto &expr = boost::get<expression>(value);
				cout<<" = ";
				(*this)(expr);
			}
			catch(std::exception &){
				auto &arg = boost::get<argument>(value);
				cout<<"(";
				printExpression()(arg);
				cout<<")";
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
		
		void operator()(const statement &value)
		{
			boost::apply_visitor(*this,value);
		}
	};
}}