#if !defined(BOOST_SPIRIT_X3_CALC9_STATEMENT_HPP)
#define BOOST_SPIRIT_X3_CALC9_STATEMENT_HPP

#include <boost/spirit/home/x3.hpp>
#include "ast.hpp"
#include "config.hpp"

namespace cpp
{
    namespace x3 = boost::spirit::x3;
    namespace parser
    {
        struct statement_class;
        typedef x3::rule<statement_class, ast::statement> statement_type;
        typedef statement_type::id statement_id;
        BOOST_SPIRIT_DECLARE(statement_type);
		
		struct statements_class;
        typedef x3::rule<statements_class, ast::statements> statements_type;
        typedef statements_type::id statements_id;
        BOOST_SPIRIT_DECLARE(statements_type);
		
    }
    
    parser::statement_type const& statement();
    parser::statements_type const& statements();
    
}

#endif
