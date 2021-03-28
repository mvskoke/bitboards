CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11 -I../../src/

OBJ = ../../obj
SRC = ../../src
UNITY = ../../unity/unity.o

DEP = $(OBJ)/test_gameops.o $(OBJ)/bitboards.o $(OBJ)/display.o \
	$(OBJ)/init.o $(OBJ)/move.o $(OBJ)/update.o

test_gameops: $(DEP)
	$(CC) $(CFLAGS) $^ $(UNITY) -o test_gameops

$(OBJ)/test_gameops.o: test_gameops.c
	$(CC) $(CFLAGS) -c $^
	mv test_gameops.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/colors.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test_gameops $(OBJ)/*.o
