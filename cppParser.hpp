#include <iostream>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <string>
#include <list>

using std::cout;
using std::endl;
using std::cin;
using namespace boost::spirit;

namespace cpp{namespace ast{
	struct symbol;
	struct string;
	struct expression;
	struct signed_;
	
	struct operand : x3::variant<double,x3::forward_ast<symbol>,x3::forward_ast<string>,
					x3::forward_ast<signed_>,x3::forward_ast<expression>>
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
		char sign;
		operand operand_;
	};
	
	struct operation
	{
		char operator_;
		operand operand_;
	};
	
	struct expression
	{
		operand first;
		std::list<operation> rest;
	};
}}

BOOST_FUSION_ADAPT_STRUCT(cpp::ast::symbol,str)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::string, str)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::signed_, sign,operand_)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::operation, operator_,operand_)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::expression, first,rest)

namespace cpp{namespace ast{
	struct printAst
	{
		void operator()(const string &value){
			cout<<value.str;
		}
		void operator()(const symbol &value){
			cout<<value.str;
		}
		void operator()(const double value){
			cout<<value;
		}
		void operator()(const signed_ &value){
			cout<<value.sign;
			boost::apply_visitor(*this,value.operand_);
		}
		void operator()(const expression &value){
			boost::apply_visitor(*this,value.first);
			for(const auto &i : value.rest){
				cout<<i.operator_;
				boost::apply_visitor(*this,i.operand_);
			}
		}
		void operator()(const operand &value)
		{
			boost::apply_visitor(*this,value);
		}
	};
}}

namespace cpp{namespace parser{
	
	using x3::ascii::alnum;
	using x3::ascii::alpha;
	using x3::char_;
	using x3::lit;
	
	x3::rule<class number,double>number = "number";
	x3::rule<class string,ast::string>string = "string";
	x3::rule<class symbol,ast::symbol>symbol = "symbol";
	x3::rule<class operand,ast::operand>operand = "operand";
	
	x3::rule<class expression,ast::expression>expression = "expression";
	x3::rule<class additive_expr,ast::expression> additive_expr = "additive_expr";
	x3::rule<class multiplicative_expr,ast::expression>multiplicative_expr = "multiplicative_expr";
	x3::rule<class unary_expr,ast::operand>unary_expr = "unary_expr";
	x3::rule<class primary_expr,ast::operand>primary_expr = "primary_expr";
	
	auto symbol_def = x3::lexeme[&(alpha|lit('_'))>>+(alnum|char_('_'))];
    auto string_def = x3::lexeme[(lit('"')>>*(char_-'"')>>lit('"'))|(lit('\'')>>*(char_-'\'')>>lit('\''))];
	auto number_def = x3::double_;
	
	auto operand_def = number | string | symbol;
	
	auto const primary_expr_def = (operand | '(' >> expression >>')');
	
	auto const unary_expr_def = primary_expr | char_('-') >> primary_expr | char_('+')>>primary_expr;
	
	auto const multiplicative_expr_def = unary_expr >> *((char_('*') >> unary_expr)|(char_('/')>>unary_expr));
	
	auto const additive_expr_def = multiplicative_expr >> *((char_('+')>>multiplicative_expr)|(char_('-')>>multiplicative_expr));
	
	auto const expression_def = additive_expr;
	
	BOOST_SPIRIT_DEFINE(symbol,number,string,operand,primary_expr,unary_expr,multiplicative_expr,
		additive_expr,expression);
}}

int main(){
	std::string input;
	cpp::ast::printAst astPrinter;
	bool status;
	while(true)
	{
		cpp::ast::expression ast;
		cout<<">> ";
		getline(cin,input);
		auto start = input.begin();
		auto end = input.end();
		status = x3::phrase_parse(start,end,cpp::parser::expression,x3::ascii::space,ast);
		if(status && start==end){
			astPrinter(ast);
			cout<<endl;
		}else{
			cout<<"Failed to parse"<<endl;
		}
	}
}