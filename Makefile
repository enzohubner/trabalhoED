# Nome do compilador
CC = gcc

# Flags para compilar com avisos e debug
CFLAGS = -Wall -Wextra -g3

# Arquivos objeto que o projeto precisa
OBJ = main.o bdpaciente.o

# Nome do executável final
TARGET = meu_programa

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c bdpaciente.h
	$(CC) $(CFLAGS) -c main.c

bdpaciente.o: bdpaciente.c bdpaciente.h
	$(CC) $(CFLAGS) -c bdpaciente.c

clean:
	rm -f $(OBJ) $(TARGET)