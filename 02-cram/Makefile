CXX = g++
CXXFLAGS = -O3

FLEX = flex
BISON = bison

LEXER = lexer.l
PARSER = parser.y
PARSER_OUTPUT = parser.tab.c parser.tab.h
LEXER_OUTPUT = lex.yy.c
EXECUTABLE = interpreter.out
INPUT_FILE = input.cram
OBJECTS = main.o lex.yy.o parser.tab.o

all: $(EXECUTABLE)

$(LEXER_OUTPUT): $(LEXER)
	$(FLEX) $(LEXER)

$(PARSER_OUTPUT): $(PARSER)
	$(BISON) -d $(PARSER) -Wcounterexamples

$(EXECUTABLE): $(LEXER_OUTPUT) $(PARSER_OUTPUT) main.cpp
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) main.cpp lex.yy.c parser.tab.c

run_simplest: $(EXECUTABLE)
	./$(EXECUTABLE) < $(INPUT_FILE)

clean:
	rm -f $(EXECUTABLE) $(LEXER_OUTPUT) $(PARSER_OUTPUT) *.o

rebuild: clean all

