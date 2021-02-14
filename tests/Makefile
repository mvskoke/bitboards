CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

OBJ = ../obj
SRC = ../src
DEP = $(OBJ)/test.o $(OBJ)/bitboards.o $(OBJ)/display.o $(OBJ)/init.o $(OBJ)/update.o

test: $(DEP)
	mv *.o $(OBJ)/
	$(CC) $(CFLAGS) $^ ../unity/unity.c -o test

$(OBJ)/test.o: test.c
	$(CC) $(CFLAGS) -c $^

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f test
