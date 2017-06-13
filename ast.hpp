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
	struct argument;
	struct triExpression;
	struct identifier;
	struct new_expr;
	struct c_cast;
	struct parameter;
	struct variable_declaration;
	struct Null
	{
		
	};
	
	struct operand : x3::variant<Null,double,x3::forward_ast<symbol>,x3::forward_ast<identifier>,x3::forward_ast<string>,
					x3::forward_ast<signed_>,x3::forward_ast<new_expr>,x3::forward_ast<c_cast>,x3::forward_ast<argument>,x3::forward_ast<expression>,x3::forward_ast<triExpression>>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	struct symbol
	{
		std::string str;
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
	
	//typedef x3::variant<x3::forward_ast<variable_declaration>
	
	struct template_argument : x3::variant<x3::forward_ast<variable_declaration>,expression>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	struct identifier_single
	{
		identifier_single(std::string n){
			name = n;
		}
		identifier_single(){
			
		}
		std::string name;
		std::vector<x3::variant<x3::forward_ast<variable_declaration>,expression>> template_params;
	};
	
	struct identifier
	{
		std::string scopeOperator;
		//std::vector<std::string> names;
		//std::vector<expression> template_params;
		std::vector<identifier_single> names;
	};
	
	struct argument
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
	
	struct new_pointer
	{
		
	};
	
	struct new_array
	{
		std::vector<expression> size;
	};
	
	
	
	struct new_declaration_open
	{
		identifier type;
		std::vector<x3::variant<new_pointer,new_array>> decl;
	};
	
	struct new_function;
	struct new_declaration_close
	{
		identifier type;
		x3::variant<new_pointer,new_array,x3::forward_ast<new_function>> decl;
	};
	
	struct new_declaration : x3::variant<new_declaration_close,new_declaration_open>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	struct new_expr
	{
		//identifier type;
		new_declaration decl;
		argument init;
	};
	
	struct c_cast
	{
		identifier type;
		expression expr;
	};
	
	
	struct declarator_ptr;
	struct declarator_rref;
	struct declarator_lref;
	struct declarator_pack;
	struct declarator_noptr;
	struct declarator_comp;
	struct declarator;
	
	struct declarator : x3::variant<x3::forward_ast<declarator_comp>
	,x3::forward_ast<declarator_ptr>,x3::forward_ast<declarator_lref>,
	x3::forward_ast<declarator_rref>,x3::forward_ast<declarator_pack>>
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
		identifier member;
		std::vector<char> pointers;
		declarator decl;
	};
	
	struct declarator_lref
	{
		declarator decl;
	};
	
	struct declarator_rref
	{
		declarator decl;
	};
	
	struct declarator_pack
	{
		declarator decl;
	};
	
	struct declarator_array
	{
		std::vector<expression> size;
	};
	
	struct declarator_init : x3::variant<expression,argument>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	struct declarator_initializer
	{
		declarator decl;
		boost::optional<declarator_init> init;
	};
	
	
	struct variable_declaration
    {
		std::vector<std::string> spec;
        identifier type;
		std::vector<declarator_initializer> decl;
    };
	
	struct parameter
	{
		std::vector<variable_declaration> param;
	};
	
	struct new_function
	{
		new_array number;
		parameter params;
	};
	
	struct declarator_function
	{
		parameter params;
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
	
    
}}

namespace cpp{ namespace ast{
	
	namespace x3 = boost::spirit::x3;
	
	
	struct statement :
        x3::variant<variable_declaration,expression>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
	
	
}}

#endif