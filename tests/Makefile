CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

OBJ = ../obj

test: $(OBJ)/test.o $(OBJ)/bb.o
	$(CC) $(CFLAGS) $^ ../unity/unity.c -o test

$(OBJ)/test.o: test.c
	$(CC) $(CFLAGS) -c $^
	mv test.o $(OBJ)/

$(OBJ)/bb.o: ../src/bb.c ../src/bb.h
	$(CC) $(CFLAGS) -c $<
	mv bb.o $(OBJ)/

clean:
	rm -f test
