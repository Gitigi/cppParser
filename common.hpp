#if !defined(COMMON_HPP)
#define COMMON_HPP

#include <boost/spirit/home/x3.hpp>
#include <string>

namespace cpp{ namespace parser{
	namespace x3 = boost::spirit::x3;
	using x3::alpha;
	using x3::char_;
	using x3::alnum;
	
	const struct reservedWords_ : x3::symbols<std::string>
	{
		reservedWords_(){
			add("asm")
			("case")
			("switch")
			("break")
			("class")
			("decltype")
			("default")
			("if")
			("else")
			("for")
			("namespace")
			("delete")
			("enum")
			("throw")
			("new");
		}
	}reservedWords;

	const auto sym = x3::rule<class sym,std::string>{} = x3::raw[x3::lexeme[!(reservedWords>>!alpha)>>(alpha|char_('_'))>>*(alnum|char_('_'))]];
	x3::rule<class symbol,ast::symbol> const symbol = "symbol";
	x3::rule<class identfier,ast::identifier> const identifier = "identifier";
	
	auto const identifier_def = -x3::string("::")>>sym % "::";
	auto const symbol_def = sym;
	BOOST_SPIRIT_DEFINE(symbol,identifier);
}}

#endif