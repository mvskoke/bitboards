#include <stdbool.h>
#include <stdio.h>

#include "bitboards.h"
#include "colors.h"
#include "display.h"

static void print_empty_square(int j, int i, bool ascii)
{
	if (ascii)
	{
		if ((j%2 == 1) ^ (i%2 == 1))
		{
			printf(ASCII_EMPTY_LIGHT);
		}
		else
		{
			printf(ASCII_EMPTY_DARK);
		}
	}
	else
	{
		if ((j%2 == 1) ^ (i%2 == 1))
		{
			printf(UTF8_EMPTY_LIGHT);
		}
		else
		{
			printf(UTF8_EMPTY_DARK);
		}
	}
}

static void print_piece(struct Bitboards *bb, int j, int i, bool ascii)
{
	if (ascii)
	{
		if ((j%2 == 1) ^ (i%2 == 1))
		{
			printf(ASCII_PIECE_LIGHT, bb->pretty_board[j][i]);
		}
		else
		{
			printf(ASCII_PIECE_DARK, bb->pretty_board[j][i]);
		}
	}
	else
	{
		if ((j%2 == 1) ^ (i%2 == 1))
		{
			printf(UTF8_PIECE_LIGHT, bb->pretty_board[j][i]);
		}
		else
		{
			printf(UTF8_PIECE_DARK, bb->pretty_board[j][i]);
		}
	}
}

void print_bb_pretty(struct Bitboards *bb, int orient, int turn, bool ascii)
{
	if (orient == turn)
	{
		puts(CURR_TURN);
	}
	else
	{
		puts(NOT_TURN);
	}
	ascii ? puts(ASCII_TOP_BOTTOM) : puts(UTF8_TOP);

	for (int i = 7; i >= 0; i--)
	{
		printf(" %d ", i+1);
		for (int j = 0; j < FILES; j++)
		{
			if (bb->pretty_board[j][i] == EMPTY_SQ)
			{
				print_empty_square(j, i, ascii);
			}
			else
			{
				// pass in entire bb instead of just the
				// piece, makes the line length shorter
				print_piece(bb, j, i, ascii);
			}
		}
		// one rank done
		ascii ? printf(ASCII_END, i+1) : printf(UTF8_END, i+1);
		if (i != 0)
		{
			ascii ? puts(ASCII_ROW) : puts(UTF8_ROW);
		}

	}
	ascii ? puts(ASCII_TOP_BOTTOM) : puts(UTF8_BOTTOM);

	if (orient != turn)
	{
		puts(CURR_TURN);
	}
	else
	{
		puts(NOT_TURN);
	}
}

// special thanks to Oscar Gutierrez Toledo for the
// formatting of this board style
// "Toledo Chess 1" - https://nanochess.org/chess.html
void print_bb_small(struct Bitboards *bb)
{
	for (int i = 7; i >= 0; i--)
	{
		printf("   %d ", i+1);
		for (int j = 0; j < FILES; j++)
		{
			printf(" %c", bb->pretty_board[j][i]);
		}
		printf("\n");
	}
	puts(SMALL_LETTERS);
}
