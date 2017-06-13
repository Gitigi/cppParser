#ifndef CONFIG_HPP_INCLUDE
#define CONFIG_HPP_INCLUDE

#include <boost/spirit/home/support/iterators/line_pos_iterator.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/spirit/home/x3.hpp>
#include <fstream>
#include "error_handler.hpp"

namespace cpp{namespace parser{
    
    using skipper_type = x3::rule<struct skipper_class,x3::unused_type const>;
    skipper_type const skipper = "skipper";
    auto const skipper_def = x3::ascii::space|x3::raw[(x3::lit("//")>>*(x3::char_-(x3::eol|x3::eoi))>>(x3::eol|x3::eoi))|
        (x3::lit("/*") >> *((x3::char_-'*')|(x3::char_('*')>>!(x3::char_('/'))))>>x3::lit("*/"))];
    BOOST_SPIRIT_DEFINE(skipper);
    
	typedef std::string::const_iterator iterator_type;
	typedef x3::phrase_parse_context<skipper_type>::type phrase_context_type;
	typedef error_handler<iterator_type> error_handler_type;
	
	typedef x3::with_context<
        error_handler_tag
      , std::reference_wrapper<error_handler_type> const
      , phrase_context_type>::type
    context_type;
	
	typedef boost::iostreams::mapped_file_source::iterator iterator_file_type;
	typedef x3::phrase_parse_context<skipper_type>::type phrase_context_file_type;
	typedef error_handler<iterator_file_type> error_handler_file_type;
	
	typedef x3::with_context<
        error_handler_tag
      , std::reference_wrapper<error_handler_file_type> const
      , phrase_context_file_type>::type
    context_file_type;
	
	
}}

#endif