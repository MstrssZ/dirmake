bin/main: src/main.c bin
	cc -Wall -Wextra -ggdb -o bin/main src/main.c

bin: 
	mkdir -p bin

run: bin/main
	./bin/main
