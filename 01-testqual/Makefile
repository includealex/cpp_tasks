LEXER = lexer.l
LEXER_C = lex.yy.c
MAIN = main.cpp
TESTQUAL = my_testqual.cpp
EXE = tq.out

all:$(EXE)

$(LEXER_C): $(LEXER)
	flex $(LEXER)

$(EXE): $(LEXER_C) $(TESTQUAL) $(MAIN)
	g++ $(LEXER_C) $(TESTQUAL) $(MAIN) -lfl -o $(EXE)

run_simplest: $(EXE)
	./$(EXE) "const char **" "char **"

valgrind_check: $(EXE)
	valgrind --leak-check=full ./$(EXE) "const char **" "char **"

clean:
	rm -f $(LEXER_C) $(EXE)

