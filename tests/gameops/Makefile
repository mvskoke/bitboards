CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

OBJ = ../../obj
SRC = ../../src
DEP = $(OBJ)/test_gameops.o $(OBJ)/bitboards.o $(OBJ)/display.o $(OBJ)/init.o $(OBJ)/move.o $(OBJ)/update.o $(SRC)/colors.h

test_gameops: $(DEP)
	$(CC) $(CFLAGS) $^ ../../unity/unity.c -o test_gameops

$(OBJ)/test_gameops.o: test_gameops.c
	$(CC) $(CFLAGS) -c $^
	mv test_gameops.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test_gameops $(OBJ)/*.o
