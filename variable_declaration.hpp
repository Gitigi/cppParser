#ifndef VARIABLE_DECLARATION_HPP
#define VARIABLE_DECLARATION_HPP

#include <boost/spirit/home/x3.hpp>
#include "ast.hpp"

namespace cpp
{
	namespace x3 = boost::spirit::x3;
	namespace parser
	{	
		struct variable_declaration_class;
		typedef x3::rule<variable_declaration_class,ast::variable_declaration> variable_declaration_type;
		typedef variable_declaration_type::id variable_declaration_id;
		BOOST_SPIRIT_DECLARE(variable_declaration_type);
		
		struct variable_declaration_single_class;
		typedef x3::rule<variable_declaration_single_class,ast::variable_declaration> variable_declaration_single_type;
		typedef variable_declaration_single_type::id variable_declaration_single_id;
		BOOST_SPIRIT_DECLARE(variable_declaration_single_type);
        
        struct declarator_initializer_class;
        typedef x3::rule<declarator_initializer_class,ast::declarator_initializer> declarator_initializer_type;
        typedef declarator_initializer_type::id declarator_initializer_id;
        BOOST_SPIRIT_DECLARE(declarator_initializer_type);
		
		struct parameter_class;
		typedef x3::rule<parameter_class,ast::parameter> parameter_type;
		typedef parameter_type::id parameter_id;
		BOOST_SPIRIT_DECLARE(parameter_type);
        
        struct function_declarator_class;
        typedef x3::rule<function_declarator_class,ast::function_declarator> function_declarator_type;
        typedef function_declarator_type::id  function_declarator_id;
        BOOST_SPIRIT_DECLARE(function_declarator_type);
        
        struct exception_specifier_class;
        typedef x3::rule<exception_specifier_class,ast::exception_specifier> exception_specifier_type;
        typedef exception_specifier_type::id exception_specifier_id;
        BOOST_SPIRIT_DECLARE(exception_specifier_type);
	}

	parser::variable_declaration_type const &variable_declaration();
    
	parser::variable_declaration_single_type const &variable_declaration_single();
	
	parser::parameter_type const &parameter();
    
    parser::function_declarator_type const &function_declarator();
    
    parser::declarator_initializer_type const &declarator_initializer();
    
    parser::exception_specifier_type const &exception_specifier();
}

#endif