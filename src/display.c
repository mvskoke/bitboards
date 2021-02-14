#include <stdio.h>

#include "bitboards.h"
#include "colors.h"
#include "display.h"

static void print_empty_square(int j, int i)
{
	if ((j%2 == 1) ^ (i%2 == 1))
	{
		printf("|   ");
	}
	else
	{
		printf("|***");
	}
}

static void print_piece(char piece, int j, int i)
{
	if ((j%2 == 1) ^ (i%2 == 1))
	{
		printf("| %c ", piece);
	}
	else
	{
		printf("|*%c*", piece);
	}
	
}

void print_bb_pretty(struct Bitboards *bb, int orient, int turn)
{
	if (orient == turn)
	{
		printf(" =>  a   b   c   d   e   f   g   h\n");
	}
	else
	{
		printf("     a   b   c   d   e   f   g   h\n");
	}
	printf("   +-------------------------------+\n");

	for (int i = 7; i >= 0; i--)
	{
		printf(" %d ", i+1);
		for (int j = 0; j < FILES; j++)
		{
			if (bb->pretty_board[j][i] == EMPTY_SQ)
			{
				print_empty_square(j, i);
			}
			else
			{
				print_piece(bb->pretty_board[j][i], j, i);
			}
		}
		// one rank done
		printf("| %d\n", i+1);
		if (i != 0)
		{
			printf("   ---------------------------------\n");
		}

	}
	printf("   +-------------------------------+\n");

	if (orient != turn)
	{
		printf(" =>  a   b   c   d   e   f   g   h\n\n");
	}
	else
	{
		printf("     a   b   c   d   e   f   g   h\n\n");
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
	printf("\n      a b c d e f g h\n\n");
}
