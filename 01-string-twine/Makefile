CXX = clang++
CXXFLAGS = -O3 -Wall -Werror -std=c++17
MAIN = main.cpp
HEADERS = string_twine.hpp
EXE = a.out

all:$(EXE)

$(EXE): $(MAIN) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(MAIN)

run_simplest: $(EXE) 
	./$(EXE) 

valgrind_check: $(EXE)
	valgrind --leak-check=full ./$(EXE)

clean:
	rm -f $(EXE)

