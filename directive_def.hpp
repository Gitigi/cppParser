#ifndef DIRECTIVE_DEF_HPP_INCLUDE
#define DIRECTIVE_DEF_HPP_INCLUDE

#include <boost/spirit/home/x3.hpp>
#include <string>
#include "ast.hpp"
#include "ast_adapted.hpp"
#include "directive.hpp"
#include "common.hpp"


namespace cpp {namespace parser{
    namespace x3 = boost::spirit::x3;
	using x3::lit;
    
    const directive_type directive = "directive";
    const x3::rule<struct define_dir,ast::define_dir> define_dir = "define_dir";
    const x3::rule<struct include_dir,ast::include_dir> include_dir = "include_dir";
    const x3::rule<struct other_dir,std::string> other_dir = "other_dir";
    
    const auto directive_body = x3::rule<struct directive_body,std::string>{} = 
        x3::raw[x3::lexeme[*((x3::char_('\\')>>(x3::eol|x3::eoi))|(x3::char_-(x3::eol|x3::eoi)))>>(x3::eol|x3::eoi)]];
	
    const auto define_param = x3::rule<struct define_param,std::vector<std::string>>{} =*(sym|x3::string("..."));
    
    auto const define_dir_def = lit("define")>>sym>>-(lit('(')>>define_param>>lit(')'))>>directive_body;
    auto const include_dir_def = lit("include")>>directive_body;
    auto const other_dir_def = directive_body;
    auto const directive_def = lit('#')>>(define_dir|include_dir|other_dir);
    
    BOOST_SPIRIT_DEFINE(
        directive,
        define_dir,
        include_dir,
        other_dir
        );
}}

namespace cpp{
	parser::directive_type const &directive(){
		return parser::directive;
	}
}

#endif
