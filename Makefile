INCLUDE=./include
SRC=./src
OBJ=./obj
BIN=./bin

all:
	gcc ./src/Shell.c -o $(OBJ)/Shell.o -I$(INCLUDE)

run:
	./$(OBJ)/Shell.o
