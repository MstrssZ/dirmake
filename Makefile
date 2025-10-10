bin/main: src/main.c
	cc -Wall -Wextra -ggdb -o bin/main src/main.c

run: bin/main
	./bin/main
