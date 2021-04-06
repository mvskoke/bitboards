CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11 -I../../src/

OBJ = ../../obj
SRC = ../../src
UNITY = ../../unity/unity.o

DEP = $(OBJ)/test_chess.o $(OBJ)/attacks.o $(OBJ)/bitboards.o \
	$(OBJ)/chess.o $(OBJ)/display.o $(OBJ)/init.o $(OBJ)/move.o \
	$(OBJ)/update.o $(OBJ)/validate.o

test_chess: $(DEP)
	$(CC) $(CFLAGS) $^ $(UNITY) -o test_chess

$(OBJ)/test_chess.o: test_chess.c
	$(CC) $(CFLAGS) -c $^
	mv test_chess.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/colors.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test_chess $(OBJ)/*.o
