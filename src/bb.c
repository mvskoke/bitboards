#include <stdint.h>
#include <stdio.h>

#include "bb.h"

/* THESE BIT FUNCTIONS RETURN THE MODIFIED BITBOARD
   BECAUSE IT MADE UNITY TESTING EASIER */

uint64_t set_bit(uint64_t *bb, const int index)
{
	*bb |= 1ULL << index;
	return *bb;
}

uint64_t flip_bit(uint64_t *bb, const int index)
{
	*bb ^= 1ULL << index;
	return *bb;
}

uint64_t clear_bb(uint64_t *bb)
{
	*bb = 0;
	return *bb;
}

uint64_t clear_bit(uint64_t *bb, const int index)
{
	// mask out the bit at int index
	// to make mask, xor UINT64_MAX with the mask's complement
	// ...1111111111
	// ...0000000100
	// ...1111111011
	uint64_t mask = UINT64_MAX;
	mask ^= (1ULL << index);
	*bb &= mask;
	return *bb;
}

int get_bit(const uint64_t bb, const int index)
{
	return (bb >> index) & 1ULL;
}

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

void print_bb_pretty(struct BitBoards *bb, int orient, int turn)
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
			if (bb->pretty_board[j][i] == '\0')
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
		printf(" =>  a   b   c   d   e   f   g   h\n");
	}
	else
	{
		printf("     a   b   c   d   e   f   g   h\n");
	}
}

void print_bb(uint64_t bb)
{
	int index;
	int curr_bit;
	int i = 0; // file
	int j = 7; // rank
	while (j != -1)
	{
		index = i + 8 * j;
		curr_bit = get_bit(bb, index);
		printf("%i", curr_bit);

		i++;
		if (i == 8)
		{
			i = 0;
			j--;
			printf("\n");
		}
		else
		{
			printf(", ");
		}
	}
	printf("\n\n");
}

void print_all_bb(struct BitBoards *bb)
{
	for (int i = 0; i < TOTAL_BB; i++)
	{
		print_bb(bb->wPieces[i]);
		print_bb(bb->bPieces[i]);
	}
	print_bb(bb->wPieces[ALL] | bb->bPieces[ALL]);
}

void init_bb(struct BitBoards *bb)
{
	/**** PIECE LOCATIONS ****/

	//                                                                                     7654 3210
	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 1111 1111 | 0000 0000
	bb->wPieces[PAWNS]      = 0x000000000000FF00;

	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0100 0010
	bb->wPieces[KNIGHTS]    = 0x0000000000000042;

	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0010 0100
	bb->wPieces[BISHOPS]    = 0x0000000000000024;

	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 1000 0001
	bb->wPieces[ROOKS]      = 0x0000000000000081;

	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 1000
	bb->wPieces[QUEENS]     = 0x0000000000000008;

	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0001 0000
	bb->wPieces[KING]       = 0x0000000000000010;

	bb->wPieces[ALL]        = 0x000000000000FFFF;

	// for black pieces, move the pawns right by 5 bytes, other pieces by 7 bytes
	bb->bPieces[PAWNS]      = 0x00FF000000000000;
	bb->bPieces[KNIGHTS]    = 0x4200000000000000;
	bb->bPieces[BISHOPS]    = 0x2400000000000000;
	bb->bPieces[ROOKS]      = 0x8100000000000000;
	bb->bPieces[QUEENS]     = 0x0800000000000000;
	bb->bPieces[KING]       = 0x1000000000000000;
	bb->bPieces[ALL]        = 0xFFFF000000000000;

	/**** PSEUDO-LEGAL ATTACKS ****/

	// we can hardcode these because it's just the setup
	bb->wAttacks[PAWNS]     = 0x00000000FFFF0000;

	// 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 1010 0101 / 0000 0000 / 0000 0000
	bb->wAttacks[KNIGHTS]   = 0x0000000000A50000;

	// you can only move pawns and knights on the first turn
	bb->wAttacks[BISHOPS]   = 0x0000000000000000;
	bb->wAttacks[ROOKS]     = 0x0000000000000000;
	bb->wAttacks[QUEENS]    = 0x0000000000000000;
	bb->wAttacks[KING]      = 0x0000000000000000;

	bb->bAttacks[PAWNS]     = 0x0000FFFF00000000;
	bb->bAttacks[KNIGHTS]   = 0x0000A50000000000;
	bb->bAttacks[BISHOPS]   = 0x0000000000000000;
	bb->bAttacks[ROOKS]     = 0x0000000000000000;
	bb->bAttacks[QUEENS]    = 0x0000000000000000;
	bb->bAttacks[KING]      = 0x0000000000000000;

	/**** PRETTY BOARD ****/
	// pretty_board[i][j]
	// i = file a-h, j = rank 1-8

	// initialize empty squares to null char
	for (int i = 0; i < FILES; i++)
	{
		for (int j = 2; j <= 5; j++)
		{
			bb->pretty_board[i][j] = '\0';
		}
	}

	for (int i = 0; i < 8; i++)
	{
		bb->pretty_board[i][1] = 'P';
		bb->pretty_board[i][6] = 'p';
	}
	bb->pretty_board[0][0] = 'R';
	bb->pretty_board[0][7] = 'r';

	bb->pretty_board[1][0] = 'N';
	bb->pretty_board[1][7] = 'n';

	bb->pretty_board[2][0] = 'B';
	bb->pretty_board[2][7] = 'b';

	bb->pretty_board[3][0] = 'Q';
	bb->pretty_board[3][7] = 'q';

	bb->pretty_board[4][0] = 'K';
	bb->pretty_board[4][7] = 'k';

	bb->pretty_board[5][0] = 'B';
	bb->pretty_board[5][7] = 'b';

	bb->pretty_board[6][0] = 'N';
	bb->pretty_board[6][7] = 'n';

	bb->pretty_board[7][0] = 'R';
	bb->pretty_board[7][7] = 'r';
}

int get_sq_index(const char* sq)
{
	// example:
	// index  0 1
	//    sq "e 2"

	int rank = 8 * (sq[1] - '1');
	// 8 * ('2' - '1')
	// 8 * (50-49)
	// 8 * 1 == 8

	int offset = sq[0] - 'a';
	// 'e' - 'a'
	// 101 - 97 == 4

	// 8 + 4 == 12
	return rank + offset;
}

// you can pass in a move or a single square. it only checks
// the first two chars
int get_piece_type(struct BitBoards *bb, char* move)
{
	int index = get_sq_index(move);
	for (int i = 0; i < TOTAL_BB; i++)
	{
		// bitboard is set at index
		if (bb->bPieces[i] & (1ULL << index))
		{
			return i;
		}
		else if (bb->wPieces[i] & (1ULL << index))
		{
			// see bb.h:
			// white piece enums are offset by 6
			return i+6;
		}
	}
	// THIS SHOULD NEVER HAPPEN.
	// YOU SHOULD VALIDATE PIECE EXISTENCE BEFORE CALLING THIS.
	return -1;
}

static void update_pretty_board(struct BitBoards *bb, int start, int end)
{
	int start_i = start % 8;
	int start_j = (start - start_i) / 8;

	int end_i = end % 8;
	int end_j = (end - end_i) / 8;
	bb->pretty_board[end_i][end_j] = bb->pretty_board[start_i][start_j];
	bb->pretty_board[start_i][start_j] = '\0';
}

// move a piece
// move should be validated BEFORE you call this func
void update_board(struct BitBoards *bb, char* move)
{
	int piece = get_piece_type(bb, move);
	int start = get_sq_index(move);
	int end = get_sq_index(move+=2);
	update_pretty_board(bb, start, end);
	switch (piece)
	{
	case BLACK_PAWN:
		// remove from start square
		flip_bit(&(bb->bPieces[PAWNS]), start);
		flip_bit(&(bb->bPieces[ALL]), start);
		// and move to end square
		set_bit(&(bb->bPieces[PAWNS]), end);
		set_bit(&(bb->bPieces[ALL]), end);
		break;
	case BLACK_KNIGHT:
		flip_bit(&(bb->bPieces[KNIGHTS]), start);
		flip_bit(&(bb->bPieces[ALL]), start);
		set_bit(&(bb->bPieces[KNIGHTS]), end);
		set_bit(&(bb->bPieces[ALL]), end);
		break;
	case BLACK_BISHOP:
		flip_bit(&(bb->bPieces[BISHOPS]), start);
		flip_bit(&(bb->bPieces[ALL]), start);
		set_bit(&(bb->bPieces[BISHOPS]), end);
		set_bit(&(bb->bPieces[ALL]), end);
		break;
	case BLACK_ROOK:
		flip_bit(&(bb->bPieces[ROOKS]), start);
		flip_bit(&(bb->bPieces[ALL]), start);
		set_bit(&(bb->bPieces[ROOKS]), end);
		set_bit(&(bb->bPieces[ALL]), end);
		break;
	case BLACK_QUEEN:
		flip_bit(&(bb->bPieces[QUEENS]), start);
		flip_bit(&(bb->bPieces[ALL]), start);
		set_bit(&(bb->bPieces[QUEENS]), end);
		set_bit(&(bb->bPieces[ALL]), end);
		break;
	case BLACK_KING:
		flip_bit(&(bb->bPieces[KING]), start);
		flip_bit(&(bb->bPieces[ALL]), start);
		set_bit(&(bb->bPieces[KING]), end);
		set_bit(&(bb->bPieces[ALL]), end);
		break;

	case WHITE_PAWN:
		flip_bit(&(bb->wPieces[PAWNS]), start);
		flip_bit(&(bb->wPieces[ALL]), start);
		set_bit(&(bb->wPieces[PAWNS]), end);
		set_bit(&(bb->wPieces[ALL]), end);
		break;
	case WHITE_KNIGHT:
		flip_bit(&(bb->wPieces[KNIGHTS]), start);
		flip_bit(&(bb->wPieces[ALL]), start);
		set_bit(&(bb->wPieces[KNIGHTS]), end);
		set_bit(&(bb->wPieces[ALL]), end);
		break;
	case WHITE_BISHOP:
		flip_bit(&(bb->wPieces[BISHOPS]), start);
		flip_bit(&(bb->wPieces[ALL]), start);
		set_bit(&(bb->wPieces[BISHOPS]), end);
		set_bit(&(bb->wPieces[ALL]), end);
		break;
	case WHITE_ROOK:
		flip_bit(&(bb->wPieces[ROOKS]), start);
		flip_bit(&(bb->wPieces[ALL]), start);
		set_bit(&(bb->wPieces[ROOKS]), end);
		set_bit(&(bb->wPieces[ALL]), end);
		break;
	case WHITE_QUEEN:
		flip_bit(&(bb->wPieces[QUEENS]), start);
		flip_bit(&(bb->wPieces[ALL]), start);
		set_bit(&(bb->wPieces[QUEENS]), end);
		set_bit(&(bb->wPieces[ALL]), end);
		break;
	case WHITE_KING:
		flip_bit(&(bb->wPieces[KING]), start);
		flip_bit(&(bb->wPieces[ALL]), start);
		set_bit(&(bb->wPieces[KING]), end);
		set_bit(&(bb->wPieces[ALL]), end);
		break;
	}
}
