#include "directive_def.hpp"
#include "config.hpp"

namespace cpp { namespace parser
{
    BOOST_SPIRIT_INSTANTIATE(directive_type, iterator_type, context_type);
    BOOST_SPIRIT_INSTANTIATE(directive_type, iterator_file_type, context_file_type);
    
}}
