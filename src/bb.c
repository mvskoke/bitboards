#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bb.h"

/* THESE BIT FUNCTIONS RETURN THE MODIFIED BITBOARD
   BECAUSE IT MADE UNITY TESTING EASIER */

int set_bit(uint64_t *bb, int index)
{
	*bb |= 1ULL << index;
	return *bb;
}

int flip_bit(uint64_t *bb, int index)
{
	*bb ^= 1ULL << index;
	return *bb;
}

int clear_bits(uint64_t *bb)
{
	*bb = 0;
	return *bb;
}

int get_bit(uint64_t bb, int index)
{
	return (bb >> index) & 1ULL;
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

void init_bb(struct BitBoards *bb)
{
	/**** PIECE LOCATIONS ****/

	//                                                                                     7654 3210
	// 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 1111 1111 / 0000 0000
	bb->wPieces[PAWNS]      = 0x000000000000FF00;

	// 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0100 0010
	bb->wPieces[KNIGHTS]    = 0x0000000000000042;

	// 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0010 0100
	bb->wPieces[BISHOPS]    = 0x0000000000000024;

	// 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 1000 0001
	bb->wPieces[ROOKS]      = 0x0000000000000081;

	// 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 1000
	bb->wPieces[QUEENS]     = 0x0000000000000008;

	// 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0001 0000
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
}

int get_sq_index(char* sq)
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
	return (rank + offset);
}


// move a piece
// move should be validated BEFORE you call this func
void update_bb(struct BitBoards *bb, int piece, int start, int end)
{
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
