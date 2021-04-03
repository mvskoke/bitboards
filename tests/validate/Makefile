CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11 -I../../src/

OBJ = ../../obj
SRC = ../../src
UNITY = ../../unity/unity.o

DEP = $(OBJ)/test_validate.o $(OBJ)/attacks.o $(OBJ)/bitboards.o \
	$(OBJ)/init.o $(OBJ)/move.o $(OBJ)/update.o $(OBJ)/validate.o

test_validate: $(DEP)
	$(CC) $(CFLAGS) $^ $(UNITY) -o test_validate

$(OBJ)/test_validate.o: test_validate.c
	$(CC) $(CFLAGS) -c $^
	mv test_validate.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h $(SRC)/colors.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test_validate $(OBJ)/*.o
