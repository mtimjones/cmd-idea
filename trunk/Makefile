# Simple Makefile for idea

idea: main.c list.c interp.c dictionary.c
	gcc -Wall -g -I ./ -o $@ $^ -lreadline

clean:
	rm -f idea
