#if !defined(COMMON_HPP)
#define COMMON_HPP

#include <boost/spirit/home/x3.hpp>
#include <string>

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
			std::string name;
			try{
				name = boost::get<std::string>(boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base);
			}
			catch(std::exception &){
				//std::string &type = variable.type;
				ast::identifier &type = variable.type;
				if(type.names.size() == 0)
				{
					auto it = std::find(spec.begin(),spec.end(),"long");
					if(it != spec.end())
					{
						variable.type.names.push_back("long");
						spec.erase(it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"signed")) != spec.end())
					{
						variable.type.names.push_back("signed");
						spec.erase(it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"unsigned")) != spec.end())
					{
						variable.type.names.push_back("unsigned");
						spec.erase(it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"short")) != spec.end())
					{
						variable.type.names.push_back("short");
						spec.erase(it);
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
					boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base = variable.type.names[0];
					
					variable.type.names[0]=type;
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
	
	static auto check_type = [](auto const &ctx){
		auto &variable = x3::_attr(ctx);
		if(variable.decl.size() > 0)
		{
			auto &spec = variable.spec;
			auto &decl = variable.decl[0].decl;
			std::string name;
			try{
				name = boost::get<std::string>(boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base);
			}
			catch(std::exception &){
				//std::string &type = variable.type;
				ast::identifier &type = variable.type;
				if(type.names.size() == 0)
				{
					auto it = std::find(spec.begin(),spec.end(),"long");
					if(it != spec.end())
					{
						variable.type.names.push_back("long");
						spec.erase(it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"signed")) != spec.end())
					{
						variable.type.names.push_back("signed");
						spec.erase(it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"unsigned")) != spec.end())
					{
						variable.type.names.push_back("unsigned");
						spec.erase(it);
					}
					else if((it=std::find(spec.begin(),spec.end(),"short")) != spec.end())
					{
						variable.type.names.push_back("short");
						spec.erase(it);
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
					boost::get<x3::forward_ast<ast::declarator_comp>>(decl).get().base = variable.type.names[0];
					
					variable.type.names[0]=type;
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
			("delete")
			("enum")
			("throw")
			("new");
		}
	}reservedWords;
	
	const struct qualifiers_ : x3::symbols<std::string>
	{
		qualifiers_(){
			add("const","const")
			("volatile","volatile")
			("mutable","mutable")
			("long","long")
			("unsigned","unsigned")
			("signed","signed")
			("short","short")
			("typedef","typedef");
		
		}
	}qualifiers;

	const auto sym = x3::rule<class sym,std::string>{} = x3::raw[x3::lexeme[!(reservedWords>>!alpha)>>(alpha|char_('_'))>>*(alnum|char_('_'))]];
	x3::rule<class symbol,ast::symbol> const symbol = "symbol";
	x3::rule<class identfier,ast::identifier> const identifier = "identifier";
	
	auto const identifier_def = -x3::string("::")>>sym % "::";
	auto const symbol_def = sym;
	BOOST_SPIRIT_DEFINE(symbol,identifier);
}}

#endif