#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "bitboards.h"
#include "colors.h"
#include "commands.h"
#include "display.h"
#include "init.h"
#include "move.h"
#include "update.h"

#define BUFFER_SIZE 1024

int main(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	struct Move *curr_move = malloc(sizeof(struct Move));
	struct Move *prev_move = malloc(sizeof(struct Move));
	init_moves(curr_move, prev_move);

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
		case RESIGN:
			printf("RESIGN\n");
			break;
		case DRAW:
			printf("DRAW\n");
			break;
		case FLIP:
			printf("FLIP\n");
			break;
		case QUIT:
			playing = false;
			break;
		case HELP:
			printf("HELP\n");
			break;
		case MOVE:
			if (parse_move(bb, curr_move, command)) {
				update_board(bb, curr_move);
			}
			break;
		}

		turn = !turn;

		// print board AFTER updating turn because the next
		// iteration starts by getting the NEXT player's command
		// and only reprint board if user entered a move command
		if (type == MOVE)
		{
			print_bb_pretty(bb, orient, turn, ascii);
			//print_bb_small(bb);
		}
	}
	free(bb);
	free(curr_move);
	free(prev_move);
	return 0;
}
