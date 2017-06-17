#ifndef AST_ADAPTED_HPP_INCLUDE
#define AST_ADAPTED_HPP_INCLUDE

#include <boost/fusion/include/adapt_struct.hpp>


BOOST_FUSION_ADAPT_STRUCT(cpp::ast::include_dir,file_loc);
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::define_dir,identifier,params,defn);

BOOST_FUSION_ADAPT_STRUCT(cpp::ast::symbol,str)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::string, str)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::identifier_single, name,template_params);
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
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::aggregate,item)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::exception_specifier,excepted)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::noexception_specifier,condition)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_function,params,exception_spec)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_comp, base,func_array)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_ptr,member,pointers,decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_lref,decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_rref,decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_pack,decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::declarator_initializer,decl,init)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::function_declarator,spec,type,name,params,exception_spec)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::block_stat,stat)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::if_stat,condition,stat,else_if,else_)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::else_if_stat,condition,stat)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::try_stat,stat,catch_)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::catch_stat,exception_,stat)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::function,decl,defn)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::class_decl_defn,members,variable)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::class_decl_variable,variable)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::class_decl,type,name,var)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::enum_defn,nested,name,type,enumerators)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::enumerator,item,isSet,value)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::class_constructor,type,name,params,defn)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::label,name)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::switch_case,condition,action)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::switch_expr,test,cases)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::for_loop,init,condition,iteration)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::for_range,init,iteration)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::for_stat,conditioning,action)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::while_stat,condition,action)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::do_stat,action,condition)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::namespace_decl,name,decl)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::namespace_alias,alias,value)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::using_directive,ns_name)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::using_declaration,name)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::using_alias,alias,value)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::template_type_parameter,typen,parameter_pack,name,default_value)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::template_template_parameter,params,type)
BOOST_FUSION_ADAPT_STRUCT(cpp::ast::template_decl,params,body)

#endif