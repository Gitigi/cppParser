#ifndef AST_HPP_INCLUDE
#define AST_HPP_INCLUDE

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/fusion/view/iterator_range.hpp>
#include <boost/fusion/include/iterator_range.hpp>
#include <boost/optional.hpp>
#include <string>
#include <list>
#include <vector>

namespace cpp{namespace ast{
    namespace x3 = boost::spirit::x3;
    
    struct define_dir
    {
        std::string identifier;
        std::vector<std::string> params;
        std::string defn;
    };
    
    struct include_dir
    {
        std::string file_loc;
    };
    
    struct directive : x3::variant<std::string,include_dir,define_dir>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
}}

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
    struct lambda;
    
	struct Null
	{
		
	};
	
	struct operand : x3::variant<Null,double,x3::forward_ast<symbol>,x3::forward_ast<identifier>,x3::forward_ast<string>,
					x3::forward_ast<signed_>,x3::forward_ast<new_expr>,x3::forward_ast<c_cast>,x3::forward_ast<argument>,
                    x3::forward_ast<expression>,x3::forward_ast<triExpression>,
                    x3::forward_ast<lambda>>
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
	
	struct expression : x3::position_tagged
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
    
    struct template_arguments : std::vector<x3::variant<x3::forward_ast<variable_declaration>,expression>>
    {
        
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
	
	struct identifier : x3::position_tagged
	{
        identifier(){};
        identifier(const std::string &value){
            names.push_back(identifier_single(value));
        }
        int length(){
            if(names.size()>0)
            {
                return names[0].name.length();
            }
            else{
                return 0;
            }
            
        }
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
		new_declaration type;
		expression expr;
	};
	
    struct aggregate;
    
    struct aggregate_item : x3::variant<expression,x3::forward_ast<aggregate>>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct aggregate
    {
        std::list<aggregate_item> item;
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
	
	struct declarator_noptr : x3::variant<identifier,declarator>
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
	
	struct declarator_init : x3::variant<expression,argument,aggregate>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	struct declarator_initializer
	{
		declarator decl;
		boost::optional<declarator_init> init;
	};
	
	
	struct variable_declaration : x3::position_tagged
    {
		std::vector<std::string> spec;
        identifier type;
		std::vector<declarator_initializer> decl;
    };
	
	struct parameter
	{
		std::vector<x3::variant<variable_declaration,std::string>> param;
	};
	
	struct new_function
	{
		new_array number;
		parameter params;
	};
    
    struct yesexception_specifier
    {
        std::list<identifier> excepted;
    };
    
    struct noexception_specifier
    {
        boost::optional<expression> condition;
    };
    
    struct exception_specifier : x3::variant<yesexception_specifier,noexception_specifier>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
	
	struct declarator_function
	{
		parameter params;
        std::list<exception_specifier> exception_spec;
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
    
    struct decl_func;
    struct decl_func_ptr;
    struct decl_func_lref;
    struct decl_func_rref;
    struct decl_function : x3::variant<x3::forward_ast<decl_func>,
        x3::forward_ast<decl_func_ptr>,
        x3::forward_ast<decl_func_lref>,
        x3::forward_ast<decl_func_rref>>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct decl_func
    {
        x3::variant<identifier,decl_function> name;
        parameter param;
    };
    
    struct decl_func_ptr
    {
        std::string pointers;
        decl_function decl;
    };
    
    struct decl_func_lref
    {
        decl_function decl;
    };
    
    struct decl_func_rref
    {
        decl_function decl;
    };
    
    struct function_declarator
    {
        std::vector<std::string> spec;
        identifier type;
        decl_function name;
        std::list<x3::variant<yesexception_specifier,noexception_specifier>> exception_spec;
    };
	
    
}}

namespace cpp{ namespace ast{
	
	namespace x3 = boost::spirit::x3;
	
	
	struct terminated_stat;
	struct nonterminated_stat;
	struct class_decl;
    struct function;
    struct enum_defn;
    struct switch_expr;
    struct do_stat;
    struct namespace_stat;
    struct using_stat;
    struct template_template_parameter;
    class class_constructor;
    
    struct template_type_parameter
    {
        std::string typen;
        std::string parameter_pack;
        std::string name;
        variable_declaration default_value;
    };
    
    struct template_parameter : 
        x3::variant<template_type_parameter,x3::forward_ast<template_template_parameter>,variable_declaration>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct template_template_parameter
    {
        std::list<template_parameter> params;
        template_type_parameter type;
    };
    
    struct template_body : x3::variant<x3::forward_ast<class_decl>,
        x3::forward_ast<function>,x3::forward_ast<enum_defn>,variable_declaration,
        x3::forward_ast<using_stat>>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct template_decl
    {
        std::list<template_parameter> params;
        template_body body;
    };
    
	struct statement :
        x3::variant<x3::forward_ast<terminated_stat>,x3::forward_ast<nonterminated_stat>>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct break_cont
    {
        std::string name;
    };
    
    struct goto_stat
    {
        identifier loc;
    };
    
    struct return_stat : x3::variant<expression,aggregate>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
	
	struct terminated_stat : x3::variant<variable_declaration,expression,x3::forward_ast<class_decl>,
        x3::forward_ast<enum_defn>,x3::forward_ast<do_stat>,
        x3::forward_ast<using_stat>,
        break_cont,goto_stat,return_stat>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	struct block_stat
	{
		std::vector<statement> stat;
	};
	
	struct else_if_stat
	{
		x3::variant<expression,variable_declaration> condition;
		statement stat;
	};
	
	struct if_stat
	{
		x3::variant<expression,variable_declaration> condition;
		statement stat;
		std::vector<else_if_stat> else_if;
		boost::optional<statement> else_;
	};
    
    struct for_loop
    {
        x3::variant<Null,expression,variable_declaration> init;
        x3::variant<Null,expression,variable_declaration> condition;
        expression iteration;
    };
    
    struct for_range
    {
        x3::variant<Null,expression,variable_declaration> init;
        expression iteration;
    };
    
    struct for_stat
    {
        x3::variant<for_loop,for_range> conditioning;
        statement action;
    };
    
    struct while_stat
	{
		x3::variant<expression,variable_declaration> condition;
		statement action;
	};
    
    struct do_stat
    {
        statement action;
        expression condition;
    };
	
	struct null_stat{};
	
	struct catch_stat
	{
		x3::variant<std::string,parameter> exception_;
		block_stat stat;
	};
	
	struct try_stat
	{
		block_stat stat;
		std::vector<catch_stat> catch_;
	};
    
    struct statements;
    
    struct function_body:x3::variant<x3::forward_ast<statements>,try_stat,std::string>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct function
    {
        function_declarator decl;
        function_body defn;
    };
	
	struct nonterminated_stat : x3::variant<block_stat,if_stat,null_stat,try_stat,function,
        x3::forward_ast<switch_expr>,for_stat,while_stat,directive,
        x3::forward_ast<namespace_stat>,template_decl,x3::forward_ast<class_constructor>>
	{
		using base_type::base_type;
		using base_type::operator=;
	};
	
	
	struct statements : std::vector<statement>
	{
	};
    
    struct lambda
    {
        parameter param;
        statements body;
    };
    
    struct label
    {
        std::string name;
    };
    
    struct derived_class
    {
        std::list<std::string> specifier;
        identifier classname;
    };
    
    struct member_spec : x3::variant<label,function,variable_declaration,x3::forward_ast<class_constructor>,
        x3::forward_ast<class_decl>,x3::forward_ast<enum_defn>,template_decl,null_stat>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct class_decl_defn
    {
        std::list<member_spec> members;
        std::vector<declarator_initializer> variable;
    };
    
    struct class_decl_variable
    {
        std::vector<declarator_initializer> variable;
    };
	
	struct class_decl
    {
        std::string type;
        identifier name;
        std::list<derived_class> bases;
        x3::variant<class_decl_defn,class_decl_variable> var;
    };
    
    struct enumerator
    {
        std::string item;
        std::string isSet;
        expression value;
    };
    
    struct enum_defn
    {
        std::string nested;
        std::string name;
        std::string type;
        std::vector<enumerator> enumerators;
    };
    
    struct member_initializer_para
    {
        identifier member;
        argument params;
        std::string pack;
    };
    
    struct member_initializer_brace
    {
        identifier member;
        argument params;
        std::string pack;
    };
    
    struct member_initializer
    {
        std::list<x3::variant<member_initializer_para,member_initializer_brace>> init;
    };
    
    struct class_constructor
    {
        char delta;
        identifier name;
        parameter params;
        std::list<x3::variant<member_initializer,exception_specifier>> init;
        boost::optional<function_body> defn;
    };
    
    struct switch_case
    {
        std::list<expression> condition;
        std::list<statement> action;
    };
    
    struct switch_item : x3::variant<switch_case,statements>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct switch_expr
    {
        expression test;
        std::list<switch_item> cases;
    };
    
    struct namespace_decl
    {
        identifier name;
        statements decl;
    };
    
    struct namespace_alias
    {
        std::string alias;
        identifier value;
    };
    
    struct namespace_stat : x3::variant<namespace_decl,namespace_alias>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct using_directive
    {
        identifier ns_name;
    };
    
    struct using_declaration
    {
        identifier name;
    };
    
    struct using_alias
    {
        std::string alias;
        identifier value;
    };
    
    struct using_stat : x3::variant<using_declaration,using_directive,using_alias>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
	
}}

#endif