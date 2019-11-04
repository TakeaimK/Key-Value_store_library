# Project: kv
# Makefile created by Dev-C++ 5.11

CPP      = g++
CC       = gcc
OBJ      = main.o
LINKOBJ  = main.o
BIN      = kv
RM       = rm -f
LIBS	 = kvlib/kvlib.a

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)
