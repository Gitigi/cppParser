#ifndef VARIABLE_DECLARATION_DEF_HPP_INCLUDE
#define VARIABLE_DECLARATION_INCLUDE

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include "ast.hpp"
#include "ast_adapted.hpp"
#include "variable_declaration.hpp"
#include "expression.hpp"
#include "common.hpp"
#include "error_handler.hpp"

#include <string>
#include <iostream>

namespace cpp{namespace parser{
	namespace x3 = boost::spirit::x3;
	using x3::lit;
    
    
	namespace {
        IMPORT_PARSER(identifier);
        IMPORT_PARSER(expression);
        IMPORT_PARSER(assignment);
        IMPORT_PARSER(argument_expr);
	}
	
	struct declarator_initializer_class;
	
	//variable declaration
	const variable_declaration_type variable_declaration("variable_declaration");
	const variable_declaration_single_type variable_declaration_single("variable_declaration_single");
	const x3::rule<struct declarator,ast::declarator>declarator="declarator";
	const x3::rule<struct declarator_noptr,ast::declarator_noptr>declarator_noptr = "declarator_noptr";
	const x3::rule<struct declarator_ptr,ast::declarator_ptr>declarator_ptr = "declarator_ptr";
	const x3::rule<struct declarator_lref,ast::declarator_lref>declarator_lref="declarator_lref";
	const x3::rule<struct declarator_rref,ast::declarator_rref>declarator_rref="declarator_rref";
	const x3::rule<struct declarator_pack,ast::declarator_pack>declarator_pack="declarator_pack";
	const x3::rule<struct declarator_array,ast::declarator_array>declarator_array = "declarator_array";
    const x3::rule<struct declarator_array_single,ast::expression> declarator_array_single = "declarator_array_single";
	const x3::rule<struct declarator_function,ast::declarator_function>declarator_function = "declarator_function";
	const x3::rule<struct declarator_func_array,ast::declarator_func_array>declarator_func_array = "declarator_func_array";
	const x3::rule<struct declarator_comp,ast::declarator_comp>declarator_comp = "declarator_comp";
	const x3::rule<struct declarator_init,ast::declarator_init>declarator_init = "declarator_init";
	const declarator_initializer_type declarator_initializer = "declarator_initializer";
	const parameter_type parameter("parameter");
    const function_declarator_type function_declarator("function_declarator");
    const x3::rule<struct aggregate_item,ast::aggregate_item>aggregate_item = "aggregate_item";
    const x3::rule<struct aggregate,ast::aggregate>aggregate = "aggregate";
	
    auto const aggregate_item_def = assignment | aggregate;
    auto const aggregate_def = lit("{")>>-(aggregate_item % ",")>>lit("}");
	auto const declarator_noptr_def = identifier | (lit('(') >> declarator >> lit(')')>>!lit("..."));
	auto const declarator_ptr_def = -(identifier>>lit("::"))>>+x3::char_('*') >> -declarator;
	auto const declarator_lref_def = lit("&")>> -declarator;
	auto const declarator_rref_def = lit("&&")>> -declarator;
	auto const declarator_pack_def = lit("...")>> -declarator;
	auto const declarator_array_single_def =lit('[')>>(expression|x3::eps)>>lit(']');
	auto const declarator_array_def = +(declarator_array_single);
	auto const declarator_function_def = lit('(')>>-(parameter)>>lit(')')
        >>-(((lit("=")>>lit("0")) | lit("overide")|lit("final")));
	auto const declarator_func_array_def = declarator_function | declarator_array;
	auto const declarator_comp_def = declarator_noptr>>-declarator_func_array;
	auto const declarator_def =  declarator_ptr|declarator_comp|declarator_rref|declarator_lref|declarator_pack;
	auto const declarator_init_def = (lit('=')>>assignment)|(lit('=')>>aggregate) | (lit('(')>>argument_expr>>lit(')'))| (aggregate);
	auto const declarator_initializer_def = -declarator>>-x3::omit[lit(":")>>x3::double_] >> -(declarator_init);
	
	static auto add_spec = [](auto &ctx){
		x3::_val(ctx).spec.push_back(x3::_attr(ctx));
	};
	
	static auto check_long = [](auto &ctx){
		auto &variable = x3::_val(ctx);
		if(variable.type.names.size() == 0 && variable.spec.size() == 0){
			x3::_pass(ctx) = false;
		}
	};
    
    auto const function_declarator_def=function_declarator_type() %= *qualifiers>>-identifier>>x3::eps[check_long]>>x3::omit[*qualifiers[add_spec]]
        >>declarator_noptr>>lit('(')>>-(parameter)>>lit(')');
	
    auto const variable_declaration_def = variable_declaration_type{} 
	%= *qualifiers>>identifier>>x3::omit[*qualifiers[add_spec]] >>(declarator_initializer|x3::eps) % ",";
	
	auto const variable_declaration_single_def = variable_declaration_single_type{} 
	%= *qualifiers>>-identifier>>x3::eps[check_long]>>x3::omit[*qualifiers[add_spec]]>>(declarator_initializer|x3::eps) % "@";
	
	auto const parameter_def = parameter_type() %= (x3::string("...")|variable_declaration_single[check_type2]) % ",";
	
	
	BOOST_SPIRIT_DEFINE(
		parameter,variable_declaration_single,variable_declaration,
        aggregate_item,
        aggregate,
		declarator_noptr,
		declarator_ptr,
		declarator_lref,
		declarator_rref,
		declarator_pack,
        declarator_array_single,
		declarator_array,
		declarator_function,
		declarator_func_array,
		declarator_comp,
		declarator_init,
		declarator_initializer,
		declarator,
        function_declarator
        )
	
	struct declarator_initializer_class : x3::annotate_on_success{};
	struct variable_declaration_class : x3::annotate_on_success{};
}}

namespace cpp{
	
	parser::variable_declaration_type const &variable_declaration()
	{
		return parser::variable_declaration;
	}
    
    parser::variable_declaration_single_type const &variable_declaration_single()
	{
		return parser::variable_declaration_single;
	}
	
	parser::parameter_type const &parameter(){
		return parser::parameter;
	}
    
    parser::function_declarator_type const &function_declarator()
    {
        return parser::function_declarator;
    }
    
    parser::declarator_initializer_type const &declarator_initializer()
    {
        return parser::declarator_initializer;
    }
	
}

#endif