CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

OBJ = ../obj

test: test.o $(OBJ)/bb.o
	$(CC) $(CFLAGS) $^ ../unity/unity.c -o test

test.o: test.c
	$(CC) $(CFLAGS) -c $^

$(OBJ)/bb.o: ../src/bb.c ../src/bb.h
	mkdir $(OBJ)
	$(CC) $(CFLAGS) -c $<
	mv bb.o $(OBJ)/

clean:
	rm -f *.o
