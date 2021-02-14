CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

OBJ = obj
SRC = src
DEP = $(OBJ)/main.o $(OBJ)/commands.o $(OBJ)/bitboards.o $(OBJ)/display.o $(OBJ)/init.o $(OBJ)/update.o

# before creating main executable, compile all object files
main: $(DEP)
	# now we can move all .o files, AFTER compiling ALL of them
	# because now they are all in the root project directory
	mv *.o $(OBJ)/
	$(CC) $(CFLAGS) $^ -o main

# main.c must be compiled in a separate
# rule because there is no main.h file
$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $^

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f main $(OBJ)/*.o
