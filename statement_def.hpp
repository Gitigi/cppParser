#if !defined(BOOST_SPIRIT_X3_CALC9_STATEMENT_DEF_HPP)
#define BOOST_SPIRIT_X3_CALC9_STATEMENT_DEF_HPP

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include "ast.hpp"
#include "ast_adapted.hpp"
#include "statement.hpp"
#include "expression.hpp"
#include "directive.hpp"
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
        auto const &directive = cpp::directive();
        IMPORT_PARSER(identifier);
		auto const &variable_declaration = cpp::variable_declaration();
        IMPORT_PARSER(expression);
		auto const& parameter = cpp::parameter();
        auto const& function_declarator = cpp::function_declarator();
        auto const& declarator_initializer = cpp::declarator_initializer();
	}
	
	struct if_stat_class;
	struct else_if_stat_class;
	struct block_stat_class;
    struct for_loop_class;
    struct for_range_class;
    struct while_stat_class;
	
	typedef x3::rule<if_stat_class,ast::if_stat> if_stat_type;
	typedef x3::rule<else_if_stat_class,ast::else_if_stat> else_if_stat_type;
    typedef x3::rule<for_loop_class,ast::for_loop> for_loop_type;
    typedef x3::rule<for_range_class,ast::for_range> for_range_type;
    typedef x3::rule<while_stat_class,ast::while_stat> while_stat_type;
    
    statement_type const statement("statement");
    statements_type const statements("statements");
	
	x3::rule<struct terminated_stat,ast::terminated_stat> terminated_stat = "terminated_stat";
	x3::rule<struct nonterminated_stat,ast::nonterminated_stat> nonterminated_stat = "nonterminated_stat";
	x3::rule<block_stat_class,ast::block_stat> block_stat = "block_stat";
	if_stat_type if_stat = "if_stat";
	else_if_stat_type else_if_stat = "else_if_stat";
    for_loop_type for_loop = "for_loop";
    for_range_type for_range = "for_range";
    x3::rule<struct for_stat,ast::for_stat> for_stat="for_stat";
    while_stat_type while_stat = "while_stat";
    x3::rule<struct do_stat,ast::do_stat>do_stat = "do_stat";
	x3::rule<struct null_stat,ast::null_stat> null_stat = "null_stat";
	x3::rule<struct try_stat,ast::try_stat>try_stat = "try_stat";
	x3::rule<struct catch_stat,ast::catch_stat>catch_stat = "catch_stat";
    x3::rule<struct function,ast::function>function = "function";
    x3::rule<struct function_body,ast::function_body>function_body = "function_body";
    
    x3::rule<struct class_decl_defn,ast::class_decl_defn>class_decl_defn="class_defn_decl";
    x3::rule<struct class_decl_variable,ast::class_decl_variable>class_decl_variable="class_defn_variable";
    x3::rule<struct class_decl,ast::class_decl>class_decl = "class_decl";
    x3::rule<struct memeber_spec,ast::member_spec>member_spec = "member_spec";
    x3::rule<struct class_constructor,ast::class_constructor>class_constructor = "class_constructor";
    x3::rule<struct label,ast::label>label = "label";
    x3::rule<struct enum_defn,ast::enum_defn>enum_defn = "enum_defn";
    x3::rule<struct enumerator,ast::enumerator>enumerator="enumerator";
    x3::rule<struct switch_case,ast::switch_case>switch_case = "switch_case";
    x3::rule<struct switch_default,ast::statements>switch_default = "switch_default";
    x3::rule<struct switch_item,ast::switch_item>switch_item = "switch_item";
    x3::rule<struct switch_expr,ast::switch_expr>switch_expr = "switch_expr";
    x3::rule<struct namespace_stat,ast::namespace_stat>namespace_stat = "namespace_stat";
    x3::rule<struct namespace_decl,ast::namespace_decl>namespace_decl = "namespace_decl";
    x3::rule<struct namespace_alias,ast::namespace_alias>namespace_alias = "namespace_alias";
    x3::rule<struct using_stat,ast::using_stat>using_stat = "using_stat";
    x3::rule<struct using_directive,ast::using_directive>using_directive = "using_directive";
    x3::rule<struct using_declaration,ast::using_declaration>using_declaration = "using_declaration";
    x3::rule<struct using_alias,ast::using_alias>using_alias = "using_alias";
	
	auto const terminated_stat_def = x3::rule<struct terminated_stat,ast::terminated_stat>() %=
	(using_stat|do_stat|enum_defn|class_decl | variable_declaration[check_type] | expression)>lit(';');
	
	auto const nonterminated_stat_def = directive|while_stat|for_stat|switch_expr|function|
        if_stat|block_stat|null_stat|try_stat|namespace_stat;
	
	auto const block_stat_def = lit('{')>>*statement>>lit('}');
	
	auto const if_stat_def= if_stat_type() %= lit("if")>>lit("(")>>(variable_declaration[check_type]|expression)>>lit(')') >>
	statement  >>*else_if_stat>> -(lit("else")>>statement);
	
	auto const else_if_stat_def = else_if_stat_type() %= lit("else")>>lit("if")>>lit("(")>>(variable_declaration[check_type]|expression)>>lit(')') >> statement;
	
	auto const for_loop_def = for_loop_type() %= (variable_declaration[check_type]|expression|x3::eps)>>
        lit(';')>>(variable_declaration[check_type]|expression|x3::eps)>>lit(';')>>(expression|x3::eps);
    
    auto const for_range_def = for_range_type() %= (variable_declaration[check_type]|expression|x3::eps)>>
        lit(':')>>expression;
    
    auto const for_stat_def = lit("for")>>lit("(")>>(for_range|for_loop)>>lit(')')>>statement;
    
    auto const while_stat_def = while_stat_type() %= 
        lit("while")>>lit("(")>>(variable_declaration[check_type]|expression)>>lit(')') >>statement;
    
    auto const do_stat_def = lit("do")>>statement>>lit("while")>>lit('(')>>expression>>lit(')');
    
    auto const null_stat_def = x3::omit[lit(";")];
	
	auto const try_stat_def = lit("try")>>block_stat>>+catch_stat;
	auto const catch_stat_def = lit("catch")>>lit("(")>>(x3::string("...")|parameter)>>lit(")")>>block_stat;
    
    static auto failParser = [](auto const &ctx){
        x3::_pass(ctx) = false;
    };
    
    auto const function_body_def = (lit('{')>>statements>>lit('}'))|try_stat|(lit('=')>>x3::string("delete")>>lit(';'))
        |(lit('=')>>x3::string("default")>>lit(';'));
    
    auto const function_def =function_declarator>>function_body;
    
    auto const class_decl_defn_def = lit("{")>>*member_spec>>lit("}")>>(declarator_initializer % ",");
    
    auto const class_decl_variable_def = (declarator_initializer % ",");
    
    auto const class_decl_def = (x3::string("class")|x3::string("struct"))>>sym>>
        (class_decl_defn|class_decl_variable);
    
    auto const member_spec_def = (enum_defn>>lit(";"))|(class_decl>>lit(";"))|(variable_declaration>>lit(';')) |label|class_constructor| function;
    
    auto const class_constructor_def = -sym >> -sym>>lit('(')>>parameter>>lit(')')>>(function_body|lit(";"));
    
    auto const label_def = sym >> lit(":");
    
    auto const enumerator_def = sym >> -x3::string("=")>>(expression|x3::eps);
    auto const enum_defn_def = lit("enum")>>-(x3::string("struct")|x3::string("class")) >> -sym >> -(lit(":")>>sym)>>
        -(lit("{")>>-(enumerator % ",")>>lit("}"));
    
    auto const switch_case_def = +(lit("case")>>expression>>lit(':'))>>statements;
    auto const switch_default_def = lit("default")>>lit(':')>>statements;
    auto const switch_item_def = switch_case|switch_default;
    auto const switch_expr_def = lit("switch")>>lit('(')>expression>lit(')')>>
        lit("{")>>*switch_item>>lit("}");
    
    auto const namespace_stat_def = -lit("inline") >> lit("namespace") >> (namespace_decl | namespace_alias);
    auto const namespace_decl_def = -identifier >> lit("{") >> statements >> lit("}");
    auto const namespace_alias_def = sym >> lit("=")>>identifier>lit(";");
    
    auto const using_stat_def = lit("using") >> (using_alias | using_directive | using_declaration);
    auto const using_directive_def = lit("namespace")>>identifier;
    auto const using_declaration_def = identifier;
    auto const using_alias_def = sym >> lit("=")>> identifier;
		
	auto const statement_def = nonterminated_stat | terminated_stat;
	auto const statements_def = *statement;

    BOOST_SPIRIT_DEFINE(statement,statements,terminated_stat,nonterminated_stat,
		block_stat,
		null_stat,
		if_stat,else_if_stat,
        for_loop,for_range,for_stat,
		try_stat,catch_stat,
        function_body,
        function,
        class_decl_defn,
        class_decl_variable,
        class_decl,
        member_spec,
        class_constructor,
        label,
        enum_defn,
        enumerator,
        switch_case,
        switch_default,
        switch_item,
        switch_expr,
        while_stat,
        do_stat,
        namespace_stat,
        namespace_decl,
        namespace_alias,
        using_stat,
        using_directive,
        using_declaration,
        using_alias
		);

    struct statement_class : x3::annotate_on_success {};
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
