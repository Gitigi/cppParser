#ifndef EXPRESSION_DEF_HPP_INCLUDE
#define EXPRESSION_DEF_HPP_INCLUDE

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include "ast.hpp"
#include "ast_adapted.hpp"
#include "expression.hpp"
#include "error_handler.hpp"

#include <string>


namespace cpp{namespace parser{
	namespace x3 = boost::spirit::x3;
	using x3::ascii::alnum;
	using x3::ascii::alpha;
	using x3::char_;
	using x3::lit;
	
	//x3::symbols<std::string,std::string>bitwise_and_op;
	x3::symbols< std::string> reservedWords;
	
	struct access_expr_class;
	struct dotBracket_class;
	struct newOperator_class;
	struct parameter_expr_class;
	struct postfix_expr_class;
	struct unary_expr_class;
	struct primary_expr_class;
	struct multiplicative_expr_class;
	struct additive_expr_class;
	struct shift_expr_class;
	struct comp_expr_class;
	struct equality_expr_class;
	struct bitwiseAnd_class;
	struct bitwiseXor_class;
	struct bitwiseOr_class;
	struct logicalAnd_class;
	struct logicalOr_class;
	struct conditional_class;
	struct assignment_class;
	struct yield_class;
	struct comma_class;
	struct expression_class;
	struct triExpression_class;
	
	namespace x3 = boost::spirit::x3;
	x3::rule<class number,double>number = "number";
	x3::rule<class string,ast::string>string = "string";
	x3::rule<class symbol,ast::symbol>symbol = "symbol";
	x3::rule<class operand,ast::operand>operand = "operand";
	
	expression_type expression = "expression";
	x3::rule<additive_expr_class,ast::expression> additive_expr = "additive_expr";
	x3::rule<shift_expr_class,ast::expression> shift_expr = "shift_expr";
	x3::rule<comp_expr_class,ast::expression> comp_expr = "comp_expr";
	x3::rule<equality_expr_class,ast::expression>equality_expr = "equality_expr";
	x3::rule<bitwiseAnd_class,ast::expression>bitwiseAnd = "bitwiseAnd";
	x3::rule<bitwiseXor_class,ast::expression>bitwiseXor = "bitwiseXor";
	x3::rule<bitwiseOr_class,ast::expression>bitwiseOr = "bitwiseOr";
	x3::rule<logicalAnd_class,ast::expression>logicalAnd = "logicalAnd";
	x3::rule<logicalOr_class,ast::expression>logicalOr = "logicalOr";
	x3::rule<conditional_class,ast::triExpression>conditional = "conditional";
	x3::rule<assignment_class,ast::expression>assignment = "assignment";
	x3::rule<yield_class,ast::operand>yield = "yield";
	x3::rule<comma_class,ast::expression>comma = "comma";
	x3::rule<postfix_expr_class,ast::signed_> postfix_expr = "postfix_expr";
	x3::rule<multiplicative_expr_class,ast::expression>multiplicative_expr = "multiplicative_expr";
	x3::rule<unary_expr_class,ast::operand>unary_expr = "unary_expr";
	x3::rule<primary_expr_class,ast::operand>primary_expr = "primary_expr";
	x3::rule<parameter_expr_class,ast::parameters>parameter_expr = "parameter_expr";
	x3::rule<access_expr_class,ast::expression>access_expr = "access_expr";
	x3::rule<dotBracket_class,ast::expression>dotBracket = "dotBracket";
	x3::rule<newOperator_class,ast::newOperator>newOperator = "newOperator";
	x3::rule<triExpression_class,ast::triExpression>triExpression = "triExpression";
	
	//auto symbol_def = x3::lexeme[!reservedWords>>&(alpha|lit('_'))>>+(alnum|char_('_'))];
	auto sym = x3::rule<class sym,std::string>{} = x3::raw[x3::lexeme[(alpha|char_('_'))>>*(alnum|char_('_'))]];
	auto symbol_def = sym;
    auto string_def = x3::lexeme[(lit('"')>>*(char_-'"')>>lit('"'))|(lit('\'')>>*(char_-'\'')>>lit('\''))];
	auto number_def = x3::double_;
	
	auto operand_def = number | string | symbol;
	
	
	
	auto const primary_expr_def = (operand | '(' > expression >')');
	
	auto const parameter_expr_def = -(expression % lit(','));
	auto const dotBracket_def = primary_expr >> * ((x3::string("[")>expression>lit(']')) | (x3::string(".")>symbol));
	auto const access_expr_def = (newOperator >> * ((x3::string("[")>expression>lit(']')) | (x3::string("(")>parameter_expr>lit(')')) | (x3::string(".")>symbol))) 
		| (primary_expr >> * ((x3::string("[")>expression>lit(']')) | (x3::string("(")>parameter_expr>lit(')')) | (x3::string(".")>symbol))) ;
	auto const newOperator_def = lit("new") > dotBracket >-(lit('(')>parameter_expr>lit(')'));
	//auto const unary_expr_def = newOperator | access_expr | char_('-') > primary_expr | char_('+')>primary_expr;
	auto const postfix_expr_def = x3::attr(std::string("+++")) >> access_expr >> lit("++") | x3::attr(std::string("---")) >> access_expr >> lit("--");
	
	auto const unary_expr_def = access_expr >> !(lit("++") | lit("--"))
		
		| x3::string("!") > primary_expr
		| x3::string("~") > primary_expr
		| x3::string("++") > primary_expr
		| x3::string("--") > primary_expr
		| x3::string("+") > primary_expr
		| x3::string("-") > primary_expr
		| x3::string("typeof") > primary_expr
		| x3::string("void") > primary_expr
		| x3::string("delete") > primary_expr
		| postfix_expr;
	
	auto multiplicativeOp = x3::rule<class multiplicativeOp,std::string>{} = 
		(	x3::string("**")
			|x3::string("*")
			|x3::string("/")
			|x3::string("%")
		) >> !lit("=");
	auto const multiplicative_expr_def = unary_expr >> *(multiplicativeOp>unary_expr);
	
	auto additiveOp = x3::rule<class additiveOp,std::string>{} = (x3::string("+")|x3::string("-")) >> !lit("=");
	auto const additive_expr_def = multiplicative_expr >> *(additiveOp>multiplicative_expr);
	
	
	auto shiftOp = x3::rule<class shiftOp,std::string>{} = (
		x3::string("<<")
		|x3::string(">>>")
		|x3::string(">>")
		) >> !lit('=');
	auto const shift_expr_def = additive_expr >> *(shiftOp>additive_expr);
	
	
	auto compOp = x3::rule<class compOp,std::string>{} = (
		x3::string("<=")
		|x3::string("<")
		|x3::string(">=")
		|x3::string("<")
		|x3::string("instanceof")
		|x3::string("in ")
		)>>!lit("=");
	auto const comp_expr_def = shift_expr >> *(compOp>shift_expr);
	
	auto const equality_expr_def = comp_expr >> *(
		(x3::string("===")>comp_expr)
		|(x3::string("!==")>comp_expr)
		|(x3::string("==")>comp_expr)
		|(x3::string("!=")>comp_expr)
		);
	
	
	auto bitwiseAndOp = x3::rule<class bitwiseAndOp,std::string>{} =  x3::string("&") >> !(lit("&")|lit("="));
	auto const bitwiseAnd_def = equality_expr >> *(bitwiseAndOp>equality_expr);
	
	auto const bitwiseXor_def = bitwiseAnd >> *(x3::string("^")>bitwiseAnd);
	
	auto bitwiseOrOp = x3::rule<class bitwiseOrOp,std::string>{} = x3::string("|") >> !(x3::string("|")|x3::string("="));
	auto const bitwiseOr_def = bitwiseXor >> *(bitwiseOrOp>bitwiseXor);
	
	auto const logicalAnd_def = bitwiseOr >> *(x3::string("&&")>bitwiseOr);
	auto const logicalOr_def = logicalAnd >> *(x3::string("||")>logicalAnd);
	
	auto const conditional_def = logicalOr >> *(char_('?')>conditional > char_(':')>conditional);
	
	auto const assignment_def = conditional >> *(
		(x3::string("+=")>conditional)
		|(x3::string("-=")>conditional)
		|(x3::string("**=")>conditional)
		|(x3::string("*=")>conditional)
		|(x3::string("/=")>conditional)
		|(x3::string("%=")>conditional)
		|(x3::string("<<=")>conditional)
		|(x3::string(">>=")>conditional)
		|(x3::string(">>>=")>conditional)
		|(x3::string("&=")>conditional)
		|(x3::string("^=")>conditional)
		|(x3::string("|=")>conditional)
		|(x3::string("=")>conditional)
		);
	
	auto const yield_def = assignment | (x3::string("yield") > assignment);
	
	auto const comma_def = assignment >> *(x3::string(",")>assignment);
	
	auto const expression_def = comma;
	
	auto const triExpression_def = expression >> *(char_('?')>triExpression > char_(':')>triExpression);
	
	BOOST_SPIRIT_DEFINE(symbol,number,string,operand,parameter_expr,primary_expr,access_expr,newOperator,unary_expr,multiplicative_expr,
		additive_expr,expression,triExpression,dotBracket,postfix_expr,shift_expr,comp_expr,equality_expr,
		bitwiseAnd,bitwiseXor,bitwiseOr,
		logicalAnd,logicalOr,conditional,assignment,
		yield,comma)
	
	struct unary_expr_class : x3::annotate_on_success{};
	struct newOperator_class : x3::annotate_on_success{};
	struct primary_expr_class : x3::annotate_on_success{};
	struct expression_class : x3::annotate_on_success,error_handler_base{};
	//struct triExpression_class : annotation_base,error_handler_base{};
}}

namespace cpp{
	parser::expression_type const &expression(){
		parser::reservedWords.add("typeof")
		("instanceof")
		("void")
		("in")
		("delete")
		("function");
		return parser::expression;
	}
}

#endif