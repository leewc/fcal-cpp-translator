CXX_DIR = ../lib/cxxtest
CXXTEST = $(CXX_DIR)/bin/cxxtestgen
CXXFLAGS = --error-printer --abort-on-fail --have-eh

FLAGS = -Wall -g

all: readInput.o regex.o scanner.o parser.o extToken.o ast.o parseResult.o
# Program files.
readInput.o:	readInput.cpp readInput.h
	g++ $(FLAGS) -c readInput.cpp 

regex.o:	regex.cpp regex.h
	g++ $(FLAGS) -c regex.cpp 

scanner.o:	scanner.cpp scanner.h regex.h
	g++ $(FLAGS) -c scanner.cpp 

parser.o: 	parser.cpp parser.h scanner.h parseResult.h extToken.h ast.h
	g++ $(FLAGS) -c parser.cpp

extToken.o: 	extToken.cpp parser.h scanner.h
	g++ $(FLAGS) -c extToken.cpp

ast.o:	ast.cpp ast.h
	g++ $(FLAGS) -c ast.cpp

parseResult.o:	parseResult.cpp parseResult.h ast.h
	g++ $(FLAGS) -c parseResult.cpp

# Testing files and targets.
run-tests:	regex_tests scanner_tests parser_tests 
	./regex_tests
	./scanner_tests
	./parser_tests
	./ast_tests
regex_tests:	regex_tests.cpp regex.o
	g++ $(FLAGS) -I$(CXX_DIR) -o regex_tests regex.o regex_tests.cpp

regex_tests.cpp:	regex.h regex_tests.h
	$(CXXTEST) $(CXXFLAGS) -o regex_tests.cpp regex_tests.h

scanner_tests:	scanner_tests.cpp scanner.o regex.o readInput.o
	g++ $(FLAGS) -I$(CXX_DIR)  -o scanner_tests \
		scanner.o regex.o readInput.o scanner_tests.cpp

scanner_tests.cpp:	scanner.o scanner_tests.h readInput.h
	$(CXXTEST) $(CXXFLAGS) -o scanner_tests.cpp scanner_tests.h

parser_tests:	parser_tests.cpp parser.o scanner.o readInput.o extToken.o regex.o parseResult.o parseResult.h extToken.h
	g++ $(FLAGS) -I$(CXX_DIR)  -o parser_tests \
		scanner.o parser.o readInput.o extToken.o regex.o parseResult.o parser_tests.cpp ast.o

parser_tests.cpp:	parser.o scanner.o extToken.o regex.o parser_tests.h readInput.h parseResult.h ast.o
	$(CXXTEST) $(CXXFLAGS) -o parser_tests.cpp parser_tests.h

ast_tests: ast_tests.cpp ast_tests.h ast.o parser.o readInput.o extToken.o regex.o scanner.o parseResult.o 
	g++ $(FLAGS) -I$(CXX_DIR) -o  ast_tests \
		ast_tests.cpp readInput.o parser.o ast.o scanner.o extToken.o regex.o parseResult.o

ast_tests.cpp: 	parser.h ast.o ast_tests.h readInput.h
	$(CXXTEST) $(CXXFLAGS) -o ast_tests.cpp ast_tests.h

clean:
	rm -Rf *.o \
		regex_tests regex_tests.cpp \
		scanner_tests scanner_tests.cpp	parser_tests parser_tests.cpp ast_tests ast_tests.cpp
