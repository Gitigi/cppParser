/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_X3_CALC9_STATEMENT_DEF_HPP)
#define BOOST_SPIRIT_X3_CALC9_STATEMENT_DEF_HPP

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include "ast.hpp"
#include "ast_adapted.hpp"
#include "statement.hpp"
#include "expression.hpp"
#include "common.hpp"
#include "error_handler.hpp"
#include <iostream>
#include <algorithm>
#include <exception>

using std::cout;
using std::cerr;
using std::endl;

namespace cpp { namespace parser
{
    using x3::raw;
    using x3::lexeme;
    using namespace x3::ascii;
	using x3::char_;
	

	struct qualifiers_ : x3::symbols<std::string>
	{
		qualifiers_(){
			add("const","const")
			("volatile","volatile")
			("mutable","mutable")
			("long","long")
			("unsigned","unsigned")
			("signed","signed")
			("short","short")
			("typedef","typedef");
		
		}
	}qualifiers;
	

    struct variable_declaration_class;
	
    typedef x3::rule<variable_declaration_class, ast::variable_declaration> variable_declaration_type;

    statement_type const statement("statement");
    variable_declaration_type const variable_declaration("variable_declaration");
	x3::rule<struct declarator,ast::declarator>declarator="declarator";
	x3::rule<struct declarator_noptr,ast::declarator_noptr>declarator_noptr = "declarator_noptr";
	x3::rule<struct declarator_ptr,ast::declarator_ptr>declarator_ptr = "declarator_ptr";
	x3::rule<struct declarator_array,ast::declarator_array>declarator_array = "declarator_array";
	x3::rule<struct declarator_function,ast::declarator_function>declarator_function = "declarator_function";
	x3::rule<struct declarator_func_array,ast::declarator_func_array>declarator_func_array = "declarator_func_array";
	x3::rule<struct declarator_comp,ast::declarator_comp>declarator_comp = "declarator_comp";
	x3::rule<struct declarator_initializer,ast::declarator_initializer> declarator_initializer = "declarator_initializer";

    // Import the expression rule
    namespace { auto const& expression = cpp::expression(); }
	
	auto declarator_noptr_def = sym | (lit('(') >> declarator >> lit(')'));
	auto declarator_ptr_def = lit('*') > declarator;
	auto argument = x3::rule<struct arguments,ast::argument>{} = sym>>-sym;
	auto declarator_array_def = char_('[')>>expression>>lit(']');
	auto declarator_function_def = char_('(')>>-(argument %(","))>>lit(')');
	auto declarator_func_array_def = declarator_function | declarator_array;
	auto declarator_comp_def = declarator_noptr>>-declarator_func_array;
	auto declarator_def =  declarator_ptr|declarator_comp;
	auto declarator_initializer_def = declarator >> -(lit('=') > expression);
	
	auto check_type = [](auto const &ctx){
		auto &variable = x3::_val(ctx);
		if(variable.decl.size() == 1)
		{
			auto &spec = variable.spec;
			auto &decl = variable.decl[0].decl;
			std::string name;
			try{
				name = boost::get<std::string>(boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base);
			}
			catch(std::exception &){
				//std::string &type = variable.type;
				ast::identifier &type = variable.type;
				if(type.names.size() == 0)
				{
					auto it = std::find(spec.begin(),spec.end(),"long");
					if(it != spec.end())
					{
						variable.type.names.push_back("long");
						spec.erase(it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"signed")) != spec.end())
					{
						variable.type.names.push_back("signed");
						spec.erase(it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"unsigned")) != spec.end())
					{
						variable.type.names.push_back("unsigned");
						spec.erase(it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"short")) != spec.end())
					{
						variable.type.names.push_back("short");
						spec.erase(it);
					}
					else
					{
						x3::_pass(ctx) = false;
					}
				}
				return;
			}
			
			if(name.length() > 0){
				x3::_pass(ctx) = true;
			}
			else if(variable.spec.size() > 0 && variable.type.names.size() > 0)
			{
				auto set_type = [&](std::string type,auto it){
					boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base = variable.type.names[0];
					
					variable.type.names[0]=type;
					spec.erase(it);
				};
				
				auto it = std::find(spec.begin(),spec.end(),"long");
				if(it != spec.end())
				{
					set_type("long",it);
				}
				else if((it = std::find(spec.begin(),spec.end(),"signed")) != spec.end())
				{
					set_type("signed",it);
				}
				else if((it = std::find(spec.begin(),spec.end(),"unsigned")) != spec.end())
				{
					set_type("unsigned",it);
				}
				else if((it = std::find(spec.begin(),spec.end(),"short")) != spec.end())
				{
					set_type("short",it);
				}
				else{
					x3::_pass(ctx) = false;
				}
			}
			else{
				x3::_pass(ctx) = false;
			}
		}
	};
	
	auto add_spec = [](auto &ctx){
		x3::_val(ctx).spec.push_back(x3::_attr(ctx));
	};
    auto variable_declaration_def = x3::rule<variable_declaration_class, ast::variable_declaration>{} 
	%= *qualifiers>>-identifier>>x3::omit[*qualifiers[add_spec]] >>(declarator_initializer|x3::eps) % ",">>x3::eps[check_type];
	
	auto const statement_def = (variable_declaration | expression);

    BOOST_SPIRIT_DEFINE(variable_declaration,statement,
		declarator_noptr,
		declarator_ptr,
		declarator_array,
		declarator_function,
		declarator_func_array,
		declarator_comp,
		declarator_initializer,
		declarator);

	struct variable_declaration_class : x3::annotate_on_success{};
    struct statement_class : error_handler_base, x3::annotate_on_success {};
}}

namespace cpp
{
    parser::statement_type const& statement()
    {
        return parser::statement;
    }
	
	
}

#endif
