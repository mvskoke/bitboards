CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11 -I../../src/

OBJ = ../../obj
SRC = ../../src
UNITY = ../../unity/unity.o

DEP = $(OBJ)/test_attacks.o $(OBJ)/attacks.o $(OBJ)/bitboards.o \
	$(OBJ)/init.o $(OBJ)/move.o $(OBJ)/update.o

test_attacks: $(DEP)
	$(CC) $(CFLAGS) $^ $(UNITY) -o test_attacks

$(OBJ)/test_attacks.o: test_attacks.c
	$(CC) $(CFLAGS) -c $^
	mv test_attacks.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/colors.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test_attacks $(OBJ)/*.o
