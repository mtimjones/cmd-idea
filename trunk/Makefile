# Simple Makefile for idea

idea: main.c list.c interp.c dictionary.c utils.c cluster.c eyeoh.c
	gcc -Wall -g -I ./ -o $@ $^ -L /usr/local/lib/ -lreadline

clean:
	rm -f idea
