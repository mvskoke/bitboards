CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

OBJ = ../obj
SRC = ../src
DEP = $(OBJ)/test.o $(OBJ)/bitboards.o $(OBJ)/display.o $(OBJ)/init.o $(OBJ)/update.o #$(OBJ)/move.o

test: $(DEP)
	$(CC) $(CFLAGS) $^ ../unity/unity.c -o test

$(OBJ)/test.o: test.c
	$(CC) $(CFLAGS) -c $^
	mv test.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test $(OBJ)/*.o
