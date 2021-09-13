PHONY: clean run fmt

CFLAGS := -g -std=c17 -Wall -Wextra

brainfuck:

clean:
	$(RM) ./brainfuck

run: brainfuck
	./brainfuck

fmt:
	clang-format -i ./brainfuck.c
