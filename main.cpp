#include "ast.hpp"
#include "statement.hpp"
#include "error_handler.hpp"
#include "config.hpp"
#include "ast_print.hpp"

#include <iostream>
#include <boost/spirit/home/x3.hpp>

using std::endl;
using std::cin;
using std::cerr;
using std::cout;

namespace x3 = boost::spirit::x3;

int main(){
	std::string input;
	cpp::ast::printStatement astPrinter;
	bool success;
	while(true)
	{
		cpp::ast::statement ast;
		cout<<">> ";
		getline(cin,input);
		
		using cpp::parser::iterator_type;
		iterator_type iter(input.begin());
		iterator_type end(input.end());
		
		using cpp::parser::error_handler_type;
		error_handler_type error_handler(iter,end,std::cerr);
		
		auto const parser = x3::with<cpp::parser::error_handler_tag>(std::ref(error_handler))
							[ cpp::statement()];
		
		success = x3::phrase_parse(iter,end,parser,x3::ascii::space,ast);
		if(success && iter==end){
			astPrinter(ast);
			cout<<endl;
		}else if(iter!=end){
			cout<<"not fully passed"<<endl;;
			astPrinter(ast);
			cout<<endl;
		}
		else{
			cout<<"Failed to parse"<<endl;
		}
	}
}