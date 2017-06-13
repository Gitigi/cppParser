#ifndef CONFIG_HPP_INCLUDE
#define CONFIG_HPP_INCLUDE

#include <boost/spirit/home/support/iterators/line_pos_iterator.hpp>
#include <boost/spirit/home/x3.hpp>
#include "error_handler.hpp"

namespace cpp{namespace parser{
	typedef boost::spirit::line_pos_iterator<std::string::const_iterator> iterator_type;
	typedef x3::phrase_parse_context<x3::ascii::space_type>::type phrase_context_type;
	typedef error_handler<iterator_type> error_handler_type;
	
	typedef x3::with_context<
        error_handler_tag
      , std::reference_wrapper<error_handler_type> const
      , phrase_context_type>::type
    context_type;
}}

#endif