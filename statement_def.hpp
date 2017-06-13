/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_X3_CALC9_STATEMENT_DEF_HPP)
#define BOOST_SPIRIT_X3_CALC9_STATEMENT_DEF_HPP

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include "ast.hpp"
#include "ast_adapted.hpp"
#include "statement.hpp"
#include "expression.hpp"
#include "error_handler.hpp"

namespace cpp { namespace parser
{
    using x3::raw;
    using x3::lexeme;
    using namespace x3::ascii;
	using x3::char_;
	
	x3::symbols<std::string> qualifiers;

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
	namespace {
		auto sym = x3::rule<class sym,std::string>{} = x3::raw[x3::lexeme[(alpha|char_('_'))>>*(alnum|char_('_'))]];
	}
	
	auto declarator_noptr_def = sym | (lit('(') >> declarator >> lit(')'));
	auto declarator_ptr_def = lit('*') > declarator;
	auto argument = x3::rule<struct arguments,ast::argument>{} = sym>>-sym;
	auto declarator_array_def = char_('[')>>expression>>lit(']');
	auto declarator_function_def = char_('(')>>-(argument %(","))>>lit(')');
	auto declarator_func_array_def = declarator_function | declarator_array;
	auto declarator_comp_def = declarator_noptr>>-declarator_func_array;
	auto declarator_def =  declarator_ptr|declarator_comp;
	auto declarator_initializer_def = declarator >> -(lit('=') > expression);
    auto const variable_declaration_def = x3::omit[*qualifiers]>>sym>>x3::omit[*qualifiers] >>declarator_initializer % ",";
	
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
		parser::qualifiers.add("const")
		("long")
		("unsigned")
		("signed");
		
		
        return parser::statement;
    }
}

#endif
