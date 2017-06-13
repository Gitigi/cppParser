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
				cout<<i<<"::";
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
		
		void operator()(const parameters &value)
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
			cout<<" * ";
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
		void operator()(const declarator_initializer &value)
		{
			(*this)(value.decl);
			//if(value.init)
			{
				cout<<" = ";
				(*this)(value.init);
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