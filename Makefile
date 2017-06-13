CXX = g++
CXXFLAGS = -c -std=c++14
OBJS = main.o expression.o statement.o
LIBS = -l boost_system

all : main

main: $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o main
	
main.o : main.cpp ast_print.hpp ast.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o main.o
	
expression.o : expression.cpp ast.hpp ast_adapted.hpp config.hpp error_handler.hpp expression.hpp expression_def.hpp
	$(CXX) $(CXXFLAGS) expression.cpp -o expression.o
	
statement.o : statement.cpp statement.hpp statement_def.hpp
	$(CXX) $(CXXFLAGS) statement.cpp -o statement.o
	
clean :
	rm $(OBJS) main