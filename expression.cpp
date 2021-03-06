#include "expression_def.hpp"
#include "config.hpp"

namespace cpp{ namespace parser{
	BOOST_SPIRIT_INSTANTIATE(expression_type,iterator_type,context_type)
	BOOST_SPIRIT_INSTANTIATE(identifier_type,iterator_type,context_type)
	BOOST_SPIRIT_INSTANTIATE(assignment_type,iterator_type,context_type)
	BOOST_SPIRIT_INSTANTIATE(argument_expr_type,iterator_type,context_type)
	
	BOOST_SPIRIT_INSTANTIATE(expression_type,iterator_file_type,context_file_type)
	BOOST_SPIRIT_INSTANTIATE(identifier_type,iterator_file_type,context_file_type)
	BOOST_SPIRIT_INSTANTIATE(assignment_type,iterator_file_type,context_file_type)
	BOOST_SPIRIT_INSTANTIATE(argument_expr_type,iterator_file_type,context_file_type)
}}