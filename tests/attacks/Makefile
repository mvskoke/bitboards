CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11

OBJ = ../../obj
SRC = ../../src
DEP = $(OBJ)/test_attacks.o $(OBJ)/attacks.o $(OBJ)/bitboards.o $(OBJ)/init.o $(OBJ)/move.o $(OBJ)/update.o $(SRC)/colors.h
UNITY = ../../obj/unity.o

test_attacks: $(DEP)
	$(CC) $(CFLAGS) $^ $(UNITY) -o test_attacks

$(OBJ)/test_attacks.o: test_attacks.c
	$(CC) $(CFLAGS) -c $^
	mv test_attacks.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test_attacks $(OBJ)/*.o
