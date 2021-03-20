CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

OBJ = ../../obj
SRC = ../../src
DEP = $(OBJ)/test_validate.o $(OBJ)/bitboards.o $(OBJ)/init.o $(OBJ)/move.o $(OBJ)/update.o $(OBJ)/validate.h $(SRC)/colors.h

test_validate: $(DEP)
	$(CC) $(CFLAGS) $^ ../../unity/unity.c -o test_validate

$(OBJ)/test_validate.o: test_validate.c
	$(CC) $(CFLAGS) -c $^
	mv test_validate.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test_validate $(OBJ)/*.o
