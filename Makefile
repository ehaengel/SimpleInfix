SIMPLE_INFIX_TARGETS	=	lib/infix_parser_utility.o \
							lib/infix_symbol.o \
							lib/infix_symbol_manager.o \
							lib/infix_parser_tree_node.o \
							lib/infix_operator_node.o \
							lib/infix_function_node.o \
							lib/infix_common_functions.o \
							lib/infix_function_manager.o \
							lib/infix_parser_tree.o \
							lib/infix_parser.o

all: main

# Simple Infix library
lib/infix_parser_utility.o: src/infix_parser_utility.h src/infix_parser_utility.cpp
	g++ src/infix_parser_utility.cpp -c -o lib/infix_parser_utility.o

lib/infix_symbol.o: src/infix_symbol.h src/infix_symbol.cpp
	g++ src/infix_symbol.cpp -c -o lib/infix_symbol.o

lib/infix_symbol_manager.o: src/infix_symbol_manager.h src/infix_symbol_manager.cpp
	g++ src/infix_symbol_manager.cpp -c -o lib/infix_symbol_manager.o

lib/infix_parser_tree_node.o: src/infix_parser_tree_node.h src/infix_parser_tree_node.cpp
	g++ src/infix_parser_tree_node.cpp -c -o lib/infix_parser_tree_node.o

lib/infix_operator_node.o: src/infix_operator_node.h src/infix_operator_node.cpp
	g++ src/infix_operator_node.cpp -c -o lib/infix_operator_node.o

lib/infix_function_node.o: src/infix_function_node.h src/infix_function_node.cpp
	g++ src/infix_function_node.cpp -c -o lib/infix_function_node.o

lib/infix_common_functions.o: src/infix_common_functions.h src/infix_common_functions.cpp
	g++ src/infix_common_functions.cpp -c -o lib/infix_common_functions.o

lib/infix_function_manager.o: src/infix_function_manager.h src/infix_function_manager.cpp
	g++ src/infix_function_manager.cpp -c -o lib/infix_function_manager.o

lib/infix_parser_tree.o: src/infix_parser_tree.h src/infix_parser_tree.cpp
	g++ src/infix_parser_tree.cpp -c -o lib/infix_parser_tree.o

lib/infix_parser.o: src/infix_parser.h src/infix_parser.cpp
	g++ src/infix_parser.cpp -c -o lib/infix_parser.o

# Simple Infix library
lib/libsimpleinfix.a: $(SIMPLE_INFIX_TARGETS)
	ar -cr lib/libsimpleinfix.a $(SIMPLE_INFIX_TARGETS)

# Main
main: src/main.cpp lib/libsimpleinfix.a
	g++ src/main.cpp -Llib -lsimpleinfix -llogfile -o main

# Clean
clean:
	rm -f lib/*.o lib/libsimpleinfix.a main
