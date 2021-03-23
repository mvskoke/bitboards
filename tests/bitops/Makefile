CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11

OBJ = ../../obj
SRC = ../../src
UNITY = ../../unity/unity.o

DEP = $(OBJ)/test_bitops.o $(OBJ)/bitboards.o $(OBJ)/display.o \
	$(OBJ)/init.o $(SRC)/colors.h

test_bitops: $(DEP)
	$(CC) $(CFLAGS) $^ $(UNITY) -o test_bitops

$(OBJ)/test_bitops.o: test_bitops.c
	$(CC) $(CFLAGS) -c $^
	mv test_bitops.o $(OBJ)/

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(OBJ)/

clean:
	rm -f test_bitops $(OBJ)/*.o
