CXX = g++
CXXFLAGS = -std=c++17 -Wall
EXE = main.out
SOURCES = comp_operator.cpp main.cpp
HEADERS = comp_operator.hpp
OBJS = $(SOURCES:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS)

run_simplest: $(EXE)
	./$(EXE)

clean:
	rm -f $(OBJS) $(EXE)

.PHONY: all clean
