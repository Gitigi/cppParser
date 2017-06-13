#ifndef AST_ADAPTED_HPP_INCLUDE
#define AST_ADAPTED_HPP_INCLUDE

#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(cpp::ast::symbol,str)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::string, str)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::identifier, scopeOperator,names)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::signed_, sign,operand_)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::operation, operator_,operand_)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::doubleOperation, firstOperator,firstOperand,secondOperator,secondOperand)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::argument, params)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::new_array, size)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::new_function, number,params)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::new_declaration_open,type, decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::new_declaration_close,type, decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::new_expr,decl,init)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::c_cast,type,expr)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::expression, first,rest)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::triExpression, first,rest)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::variable_declaration, spec, type,decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_array,size)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::parameter,param)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_function,params)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_comp, base,func_array)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_ptr,member,pointers,decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_lref,decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_rref,decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_pack,decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_initializer,decl,init)

#endif