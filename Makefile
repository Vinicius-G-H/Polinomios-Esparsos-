CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

SHELL := /bin/bash

MAIN_EXEC = programa
GERADOR_EXEC = gerador

MAIN_SRCS = main.c polinomio.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

GERADOR_SRCS = gerador.c
GERADOR_OBJS = $(GERADOR_SRCS:.c=.o)

all: $(MAIN_EXEC) $(GERADOR_EXEC)

$(MAIN_EXEC): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJS)

$(GERADOR_EXEC): $(GERADOR_OBJS)
	$(CC) $(CFLAGS) -o $@ $(GERADOR_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run-test: all
	./$(GERADOR_EXEC) > entrada.txt
	time ./$(MAIN_EXEC) < entrada.txt > saida.txt

clean:
	rm -f $(MAIN_OBJS) $(GERADOR_OBJS) $(MAIN_EXEC) $(GERADOR_EXEC) entrada.txt saida.txt

.PHONY: all clean run-test
