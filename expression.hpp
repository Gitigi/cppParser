#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <boost/spirit/home/x3.hpp>
#include "ast.hpp"

namespace cpp
{
	namespace x3 = boost::spirit::x3;
	namespace parser
	{
		struct expression_class;
		
		typedef x3::rule<expression_class,ast::expression>expression_type;
		typedef expression_type::id expression_id;
		
		BOOST_SPIRIT_DECLARE(expression_type)
	}
	
	parser::expression_type const &expression();
}

#endif