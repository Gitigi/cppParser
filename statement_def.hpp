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
	
	namespace {
		auto const &variable_declaration = cpp::variable_declaration();
		auto const &parameter = cpp::parameter();
	}

    struct variable_declaration_class;
	
    typedef x3::rule<variable_declaration_class, ast::variable_declaration> variable_declaration_type;

    statement_type const statement("statement");

    namespace {
		auto const& expression = cpp::expression(); 
		
	}
	
		
	auto const statement_def = x3::rule<statement_class,ast::statement>{} %= (variable_declaration[check_type] | expression);

    BOOST_SPIRIT_DEFINE(statement);

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
