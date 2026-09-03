# Compilador e Flags 
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

# Executáveis
MAIN_EXEC = programa
GERADOR_EXEC = gerador

# Arquivos Fonte e Objetos
MAIN_SRCS = main.c estrutura.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

GERADOR_SRCS = gerador.c
GERADOR_OBJS = $(GERADOR_SRCS:.c=.o)

# Compila o programa e o gerador de testes
all: $(MAIN_EXEC) $(GERADOR_EXEC)

# Compilação do Executável Principal
$(MAIN_EXEC): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJS)

# Compilação do Gerador de Testes
$(GERADOR_EXEC): $(GERADOR_OBJS)
	$(CC) $(CFLAGS) -o $@ $(GERADOR_OBJS)

# Compilação de Arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Medição de Desempenho 
run-test: all
	./$(GERADOR_EXEC) > entrada.txt
	time ./$(MAIN_EXEC) < entrada.txt

# Limpeza de Arquivos Temporários e Executáveis
clean:
	rm -f $(MAIN_OBJS) $(GERADOR_OBJS) $(MAIN_EXEC) $(GERADOR_EXEC) entrada.txt

.PHONY: all clean run-test
