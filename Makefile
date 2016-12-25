.PHONY: run clean

main: main.c main.h
	gcc -std=c99 -Wall -Werror main.c main.h -o main -pthread

run:
	./main

clean:
	rm -f main
