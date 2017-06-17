#if !defined(COMMON_HPP)
#define COMMON_HPP

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <string>
#include <iostream>

#define IMPORT_PARSER(parser) \
    auto const& parser = parser##_type(#parser) %= cpp::parser();

namespace cpp{ namespace parser{
	namespace x3 = boost::spirit::x3;
	using x3::alpha;
	using x3::char_;
	using x3::alnum;
	
	static auto check_type2 = [](auto const &ctx){
		auto &variable = x3::_attr(ctx);
		if(variable.decl.size() > 0)
		{
			auto &spec = variable.spec;
			auto &decl = variable.decl[0].decl;
			ast::identifier name;
			try{
				name = boost::get<ast::identifier>(boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base);
			}
			catch(std::exception &){
				ast::identifier &type = variable.type;
				if(type.names.size() == 0)
				{
					auto set_type = [&](std::string type,auto it){
						variable.type.names.push_back(ast::identifier_single(type));
						spec.erase(it);
					};
					auto it = std::find(spec.begin(),spec.end(),"long");
					if(it != spec.end())
					{
						set_type("long",it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"signed")) != spec.end())
					{
						set_type("signed",it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"unsigned")) != spec.end())
					{
						set_type("unsigned",it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"short")) != spec.end())
					{
						set_type("short",it);
					}
					else
					{
						x3::_pass(ctx) = false;
					}
				}
				return;
			}
			
			if(name.length() > 0){
				x3::_pass(ctx) = true;
			}
			else if(variable.spec.size() > 0 && variable.type.names.size() > 0)
			{
				auto set_type = [&](std::string type,auto it){
					boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base = variable.type.names[0].name;
					
					variable.type.names[0].name=type;
					spec.erase(it);
				};
				
				auto it = std::find(spec.begin(),spec.end(),"long");
				if(it != spec.end())
				{
					set_type("long",it);
				}
				else if((it = std::find(spec.begin(),spec.end(),"signed")) != spec.end())
				{
					set_type("signed",it);
				}
				else if((it = std::find(spec.begin(),spec.end(),"unsigned")) != spec.end())
				{
					set_type("unsigned",it);
				}
				else if((it = std::find(spec.begin(),spec.end(),"short")) != spec.end())
				{
					set_type("short",it);
				}
			}
		}
	};
    
    static auto declarator_null = [](const ast::declarator &decl)->bool {
        try{
            ast::identifier name = boost::get<ast::identifier>(boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base);
            if(name.length() > 0)
                return true;
            else
                return false;
        }
        catch(std::exception &)
        {
            return true;
        }
    };
	
	static auto check_type = [](auto const &ctx){
		auto &variable = x3::_attr(ctx);
		if(variable.decl.size() > 0)
		{
			auto &spec = variable.spec;
			auto &decl = variable.decl[0].decl;
			ast::identifier name;
			try{
				name = boost::get<ast::identifier>(boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base);
			}
			catch(std::exception &){
				//TODO : check other type of declarator (ptr,lref,rref &pack) if they are null
                if(const auto *ptr = boost::get<x3::forward_ast<ast::declarator_ptr>>(&decl))
                {
                    x3::_pass(ctx) = declarator_null(ptr->get().decl);
                    return;
                }
                
                else if(const auto *lref = boost::get<x3::forward_ast<ast::declarator_lref>>(&decl))
                {
                    x3::_pass(ctx) = declarator_null(lref->get().decl);
                    return;
                }
                
                else if(const auto *rref = boost::get<x3::forward_ast<ast::declarator_rref>>(&decl))
                {
                    x3::_pass(ctx) = declarator_null(rref->get().decl);
                    return;
                }
                
                else if(const auto *pack = boost::get<x3::forward_ast<ast::declarator_pack>>(&decl))
                {
                    x3::_pass(ctx) = declarator_null(pack->get().decl);
                    return;
                }
                
				ast::identifier &type = variable.type;
				if(type.names.size() == 0)
				{
					auto set_type = [&](std::string type,auto it){
						variable.type.names.push_back(ast::identifier_single(type));
						spec.erase(it);
					};
					
					auto it = std::find(spec.begin(),spec.end(),"long");
					if(it != spec.end())
					{
						set_type("long",it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"signed")) != spec.end())
					{
						set_type("signed",it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"unsigned")) != spec.end())
					{
						set_type("unsigned",it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"short")) != spec.end())
					{
						set_type("short",it);
					}
					else
					{
						x3::_pass(ctx) = false;
					}
				}
				return;
			}
			
			if(name.length() > 0){
				x3::_pass(ctx) = true;
			}
			else if(variable.spec.size() > 0 && variable.type.names.size() > 0)
			{
				auto set_type = [&](std::string type,auto it){
					boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base = variable.type.names[0].name;
					
					variable.type.names[0].name=type;
					spec.erase(it);
				};
				
				auto it = std::find(spec.begin(),spec.end(),"long");
				if(it != spec.end())
				{
					set_type("long",it);
				}
				else if((it = std::find(spec.begin(),spec.end(),"signed")) != spec.end())
				{
					set_type("signed",it);
				}
				else if((it = std::find(spec.begin(),spec.end(),"unsigned")) != spec.end())
				{
					set_type("unsigned",it);
				}
				else if((it = std::find(spec.begin(),spec.end(),"short")) != spec.end())
				{
					set_type("short",it);
				}
				else{
					x3::_pass(ctx) = false;
				}
			}
			else{
				x3::_pass(ctx) = false;
			}
		}
	};
    
    
	
	const struct reservedWords_ : x3::symbols<std::string>
	{
		reservedWords_(){
			add("asm")
			("case")
			("switch")
			("break")
			("class")
			("decltype")
			("default")
			("if")
			("else")
			("for")
			("namespace")
            ("using")
			("delete")
			("enum")
			("throw")
			("new")
			("try")
			("catch")
            ("static")
            ("virtual")
            ("template")
            ("const");
		}
	}reservedWords;
	
	const struct qualifiers_ : x3::symbols<std::string>,x3::annotate_on_success
	{
		qualifiers_(){
			add("const","const")
			("volatile","volatile")
			("mutable","mutable")
			("long","long")
			("unsigned","unsigned")
			("signed","signed")
			("short","short")
			("typedef","typedef")
            ("static","static")
            ("virtual","virtual");
		
		}
	}qualifiers;
    
    const struct operators_ : x3::symbols<std::string>
    {
        operators_(){
            add("operator()","operator()")
                ("operator[]","operator[]")
                ("operator+","operator+")
                ("operator-","operator-")
                ("operator*","operator*")
                ("operator/","operator/")
                ("operator%","operator%")
                ("operator=","operator=")
                ("operator>>","operator>>")
                ("operator<<","operator<<");
        }
    }operators;

	const auto sym = x3::rule<class sym,std::string>{} = x3::raw[operators|x3::lexeme[!(reservedWords>>!(alpha|char_('_')))>>(alpha|char_('_'))>>*(alnum|char_('_'))]];
	x3::rule<class symbol,ast::symbol> const symbol = "symbol";
	auto const symbol_def = sym;
	BOOST_SPIRIT_DEFINE(symbol);
}}

#endif