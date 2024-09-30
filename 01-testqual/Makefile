LEXER = lexer.l
LEXER_C = lex.yy.c
MAIN = main.cpp
TESTQUAL = my_testqual.cpp
TESTDIR = tests
TEST_SCR = test.py
GEN_TEST_DIR = gen_test_dir

EXE = tq.out

all:$(EXE)

$(LEXER_C): $(LEXER)
	flex $(LEXER)

$(EXE): $(LEXER_C) $(TESTQUAL) $(MAIN)
	g++ $(LEXER_C) $(TESTQUAL) $(MAIN) -lfl -o $(EXE)

run_simplest: $(EXE)
	./$(EXE) "const char **" "char **"

test_generated: $(EXE)
	python3 $(TESTDIR)/$(TEST_SCR)

valgrind_check: $(EXE)
	valgrind --leak-check=full ./$(EXE) "const char **" "char **"

clean:
	rm -rf $(LEXER_C) $(EXE) $(GEN_TEST_DIR)

