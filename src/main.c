#include <stdio.h>
#include <stdlib.h>

#include "bb.h"
#include "colors.h"
#include "commands.h"

#define BUFFER_SIZE 1024

int main(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	int turn = WHITE;
	int orient = BLACK;
	char buffer[BUFFER_SIZE];
	char *command = NULL;
	int type;

	print_bb_pretty(bb, orient, turn);
	int playing = 1;
	while (playing)
	{
		do
		{
			command = get_command(buffer, BUFFER_SIZE, turn);
			type = validate_command(command);
		} while (type == ILLEGAL);

		switch (type)
		{
		case RESIGN: break;
		case DRAW:   break;
		case FLIP:   break;
		case QUIT:   playing = 0; break;
		case HELP:   break;
		case MOVE:
			update_board(bb, command);
			print_bb_pretty(bb, orient, turn);
			break;
		}

		if (type != ILLEGAL)
		{
			turn = !turn;
		}
	}
	free(bb);
	return 0;
}

