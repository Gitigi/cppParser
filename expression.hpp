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
		
		struct identifier_class;
		typedef x3::rule<identifier_class,ast::identifier> identifier_type;
		typedef identifier_type::id identifier_id;
		BOOST_SPIRIT_DECLARE(identifier_type);
        
        struct function_declarator_class;
        typedef x3::rule<function_declarator_class,ast::function_declarator> function_declarator_type;
        typedef function_declarator_type::id  function_declarator_id;
        BOOST_SPIRIT_DECLARE(function_declarator_type);
	}
	
	parser::expression_type const &expression();
	
	parser::variable_declaration_type const &variable_declaration();
	
	parser::identifier_type const &identifier();
	
	parser::parameter_type const &parameter();
    
    parser::function_declarator_type const &function_declarator();
    
    parser::declarator_initializer_type const &declarator_initializer();
}

#endif