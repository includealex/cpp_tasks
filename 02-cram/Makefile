CXX = g++
CXXFLAGS = -std=c++11

LEXER = lexer.l
PARSER = parser.cpp
MAIN = main.cpp

TARGET = interpreter.out

all: $(TARGET)

$(TARGET): $(LEXER) $(PARSER) $(MAIN)
	flex -o lexer.cpp $(LEXER)
	$(CXX) $(CXXFLAGS) lexer.cpp $(PARSER) $(MAIN) -o $(TARGET)

run_simplest: $(TARGET)
	./$(TARGET) < input.cram

clean:
	rm -f lexer.cpp $(TARGET)

.PHONY: all clean run_simplest

