#if !defined(DIRECTIVE_HPP_INCLUDE)
#define DIRECTIVE_HPP_INCLUDE

#include <boost/spirit/home/x3.hpp>
#include "ast.hpp"


namespace cpp
{
    namespace x3 = boost::spirit::x3;
    namespace parser
    {
        struct directive_class;
        typedef x3::rule<directive_class, ast::directive> directive_type;
        typedef directive_type::id directive_id;
        BOOST_SPIRIT_DECLARE(directive_type);
		
    }
    
    parser::directive_type const& directive();
    
}

#endif
