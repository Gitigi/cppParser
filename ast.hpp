#ifndef AST_HPP_INCLUDE
#define AST_HPP_INCLUDE

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/view/iterator_range.hpp>
#include <boost/fusion/include/iterator_range.hpp>
#include <boost/optional.hpp>
#include <string>
#include <list>

namespace cpp{namespace ast{
	
	namespace x3 = boost::spirit::x3;
	
	struct symbol;
	struct string;
	struct expression;
	struct signed_;
	struct parameters;
	struct triExpression;
	struct identifier;
	struct new_expr;
	struct Null
	{
		
	};
	
	struct operand : x3::variant<Null,double,x3::forward_ast<symbol>,x3::forward_ast<identifier>,x3::forward_ast<string>,
					x3::forward_ast<signed_>,x3::forward_ast<new_expr>,x3::forward_ast<parameters>,x3::forward_ast<expression>,x3::forward_ast<triExpression>>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	struct symbol
	{
		std::string str;
	};
	
	struct identifier
	{
		std::string scopeOperator;
		std::vector<std::string> names;
	};
	
	struct string
	{
		std::string str;
	};
	
	struct signed_
	{
		std::string sign;
		operand operand_;
	};
	
	struct operation
	{
		std::string operator_;
		operand operand_;
	};
	
	struct expression
	{
		operand first;
		std::list<operation> rest;
	};
	
	struct parameters
	{
		std::list<expression> params;
	};
	
	struct doubleOperation
	{
		char firstOperator;
		operand firstOperand;
		char secondOperator;
		operand secondOperand;
	};
	
	struct triExpression
	{
		operand first;
		std::list<doubleOperation> rest;
	};
	
	struct new_expr
	{
		expression expr;
	};
    
}}

namespace cpp{ namespace ast{
	
	namespace x3 = boost::spirit::x3;
	
	struct declarator_ptr;
	struct declarator_noptr;
	struct declarator_comp;
	struct declarator;
	
	struct declarator : x3::variant<x3::forward_ast<declarator_comp>
	,x3::forward_ast<declarator_ptr>>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	struct declarator_noptr : x3::variant<std::string,declarator>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	struct declarator_ptr
	{
		declarator decl;
	};
	
	struct declarator_array
	{
		char brace;
		expression size;
	};
	
	struct argument
	{
		std::string type;
		std::string name;
	};
	
	struct declarator_function
	{
		char brace;
		std::list<argument> params;
	};
	
	struct declarator_func_array : x3::variant<declarator_function,declarator_array>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	struct declarator_comp
	{
		declarator_noptr base;
		boost::optional<declarator_func_array> func_array;
	};
	
	struct declarator_initializer
	{
		declarator decl;
		expression init;
	};
	
	
	struct variable_declaration
    {
		std::vector<std::string> spec;
        identifier type;
		std::vector<declarator_initializer> decl;
    };
	
	struct statement :
        x3::variant<variable_declaration,expression>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
	
	
}}

#endif