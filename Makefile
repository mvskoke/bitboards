CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

main: obj/main.o obj/bb.o obj/commands.o
	$(CC) $(CFLAGS) $^ -o main

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c $^
	mv main.o obj/

obj/bb.o: src/bb.c src/bb.h
	$(CC) $(CFLAGS) -c $<
	mv bb.o obj/

obj/commands.o: src/commands.c src/commands.h
	$(CC) $(CFLAGS) -c $<
	mv commands.o obj/

clean:
	rm -f main obj/main.o obj/bb.o obj/commands.o 
