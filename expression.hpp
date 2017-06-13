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
		
		struct identifier_class;
		typedef x3::rule<identifier_class,ast::identifier> identifier_type;
		typedef identifier_type::id identifier_id;
		BOOST_SPIRIT_DECLARE(identifier_type);
        
        struct assignment_class;
        typedef x3::rule<assignment_class,ast::expression> assignment_type;
        typedef assignment_type::id  assignment_id;
        BOOST_SPIRIT_DECLARE(assignment_type);
        
        
        struct argument_expr_class;
        typedef x3::rule<argument_expr_class,ast::argument> argument_expr_type;
        typedef argument_expr_type::id argument_expr_id;
        BOOST_SPIRIT_DECLARE(argument_expr_type);
	}
	
	parser::expression_type const &expression();
	
	parser::identifier_type const &identifier();
    
    parser::assignment_type const &assignment();
    
    parser::argument_expr_type const &argument_expr();
}

#endif