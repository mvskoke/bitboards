CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11 -I../../src/

OBJ = ../../obj
SRC = ../../src
UNITY = ../../unity/unity.o

DEP = $(OBJ)/test_chess_init.o $(OBJ)/attacks.o $(OBJ)/bitboards.o \
	$(OBJ)/display.o $(OBJ)/init.o $(OBJ)/move.o $(OBJ)/update.o

test_chess_init: $(DEP)
	$(CC) $(CFLAGS) $^ $(UNITY) -o test_chess_init

$(OBJ)/test_chess_init.o: test_chess_init.c
	$(CC) $(CFLAGS) -c $^
	mv test_chess_init.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/colors.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test_chess_init $(OBJ)/*.o
