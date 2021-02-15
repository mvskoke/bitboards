#include <stdbool.h>
#include <stdlib.h>

#include "bitboards.h"
#include "colors.h"
#include "commands.h"
#include "display.h"
#include "init.h"
#include "update.h"

#define BUFFER_SIZE 1024

int main(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	int turn = WHITE;
	// comment out this orient variable if
	// you use print_bb_small()
	int orient = BLACK;
	bool ascii = false;

	char buffer[BUFFER_SIZE];
	char *command = NULL;
	int type;

	print_bb_pretty(bb, orient, turn, ascii);
	//print_bb_small(bb);

	bool playing = true;
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
		case QUIT:   playing = false; break;
		case HELP:   break;
		case MOVE:
			update_board(bb, command);
			print_bb_pretty(bb, orient, turn, ascii);
			//print_bb_small(bb);
			break;
		}

		// if command was illegal, the next iteration should
		// not change the current color
		if (type != ILLEGAL)
		{
			turn = !turn;
		}
	}
	free(bb);
	return 0;
}

