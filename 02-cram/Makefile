# Compiler and flags
CXX = g++
CXXFLAGS = -lfl

# Source files
MAIN_SRC = main.cpp
LEX_SRC = lex.yy.c
PARSER_SRC = parser.cpp
GLOBAL_SRC = globals.cpp  # Add globals.cpp to the sources

# Executable
EXECUTABLE = interpreter.out

# Input file
INPUT_FILE = input.cram

# Targets
.PHONY: all clean run_simplest

# Default target to build the executable
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(MAIN_SRC) $(LEX_SRC) $(PARSER_SRC) $(GLOBAL_SRC)
	$(CXX) -o $(EXECUTABLE) $(MAIN_SRC) $(LEX_SRC) $(PARSER_SRC) $(GLOBAL_SRC) $(CXXFLAGS)

# Rule to generate lex.yy.c from lexer.l
$(LEX_SRC): lexer.l
	flex lexer.l

# Rule to run the simplest interpreter with input file
run_simplest: all
	./$(EXECUTABLE) $(INPUT_FILE)

# Clean up generated files
clean:
	rm -f $(EXECUTABLE) $(LEX_SRC) lex.yy.c *.o
