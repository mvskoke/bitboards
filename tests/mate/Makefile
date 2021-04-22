CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11 -I../../src/

OBJ = ../../obj
SRC = ../../src
UNITY = ../../unity/unity.o

DEP = $(OBJ)/test_mate.o $(OBJ)/attacks.o $(OBJ)/bitboards.o \
	$(OBJ)/init.o $(OBJ)/mate.o $(OBJ)/move.o $(OBJ)/update.o \
	$(OBJ)/validate.o

test_mate: $(DEP)
	$(CC) $(CFLAGS) $^ $(UNITY) -o test_mate

$(OBJ)/test_mate.o: test_mate.c
	$(CC) $(CFLAGS) -c $^
	mv test_mate.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/colors.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test_mate $(OBJ)/*.o
