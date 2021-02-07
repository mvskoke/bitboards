CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

main: obj/main.o obj/bb.o
	$(CC) $(CFLAGS) $^ -o main

obj/bb.o: src/bb.c src/bb.h
	$(CC) $(CFLAGS) -c $<
	mv bb.o obj/

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c $^
	mv main.o obj/

clean:
	rm -f main obj/*.o
