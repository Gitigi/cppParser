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
		auto const &identifier = cpp::identifier();
		auto const &variable_declaration = cpp::variable_declaration();
		auto const& expression = cpp::expression();
		auto const& parameter = cpp::parameter();
	}
	
	struct if_stat_class;
	struct else_if_stat_class;
	struct block_stat_class;
	
	typedef x3::rule<if_stat_class,ast::if_stat> if_stat_type;
	typedef x3::rule<else_if_stat_class,ast::else_if_stat> else_if_stat_type;

    statement_type const statement("statement");
    statements_type const statements("statements");
	
	x3::rule<struct terminated_stat,ast::terminated_stat> terminated_stat = "terminated_stat";
	x3::rule<struct nonterminated_stat,ast::nonterminated_stat> nonterminated_stat = "nonterminated_stat";
	x3::rule<block_stat_class,ast::block_stat> block_stat = "block_stat";
	if_stat_type if_stat = "if_stat";
	else_if_stat_type else_if_stat = "else_if_stat";
	x3::rule<struct null_stat,ast::null_stat> null_stat = "null_stat";
	x3::rule<struct try_stat,ast::try_stat>try_stat = "try_stat";
	x3::rule<struct catch_stat,ast::catch_stat>catch_stat = "catch_stat";
	
	auto const terminated_stat_def = x3::rule<struct terminated_stat,ast::terminated_stat>() %=
	(variable_declaration[check_type] | expression)>>lit(';');
	
	auto const nonterminated_stat_def = if_stat|block_stat|null_stat|try_stat;
	
	auto const block_stat_def = lit('{')>>*statement>>lit('}');
	
	auto const if_stat_def= if_stat_type() %= lit("if")>>lit("(")>>(variable_declaration[check_type]|expression)>>lit(')') >>
	statement  >>*else_if_stat>> -(lit("else")>>statement);
	
	auto const else_if_stat_def = else_if_stat_type() %= lit("else")>>lit("if")>>lit("(")>>(variable_declaration[check_type]|expression)>>lit(')') >> statement;
	
	auto const null_stat_def = x3::omit[lit(";")];
	
	auto const try_stat_def = lit("try")>>block_stat>>+catch_stat;
	auto const catch_stat_def = lit("catch")>>lit("(")>>(x3::string("...")|parameter)>>lit(")")>>block_stat;
		
	auto const statement_def = terminated_stat | nonterminated_stat;
	auto const statements_def = *statement;

    BOOST_SPIRIT_DEFINE(statement,statements,terminated_stat,nonterminated_stat,
		block_stat,
		null_stat,
		if_stat,else_if_stat,
		try_stat,catch_stat
		);

    struct statement_class : error_handler_base, x3::annotate_on_success {};
    struct statements_class : error_handler_base, x3::annotate_on_success {};
    struct block_stat_class : x3::annotate_on_success {};
    struct if_stat_class : x3::annotate_on_success {};
    struct else_if_stat_class : x3::annotate_on_success {};
}}

namespace cpp
{
    parser::statement_type const& statement()
    {
        return parser::statement;
    }
	
	parser::statements_type const& statements()
    {
        return parser::statements;
    }
	
}

#endif
