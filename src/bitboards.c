#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitboards.h"

/* THESE BIT FUNCTIONS RETURN THE MODIFIED BITBOARD
   BECAUSE IT MADE UNITY TESTING EASIER */

U64 set_bit(U64 *bb, const int index)
{
	*bb |= 1ULL << index;
	return *bb;
}

U64 flip_bit(U64 *bb, const int index)
{
	*bb ^= 1ULL << index;
	return *bb;
}

U64 clear_bb(U64 *bb)
{
	*bb = 0;
	return *bb;
}

U64 clear_bit(U64 *bb, const int index)
{
	// mask out the bit at int index
	// to make mask, xor UINT64_MAX with the mask's complement
	// the complement of mask is just one bit set at the mask's index
	// ...1111111111
	// ...0000000100
	// ...1111111011
	U64 mask = UINT64_MAX;
	mask ^= (1ULL << index);
	*bb &= mask;
	return *bb;
}

bool get_bit(const U64 bb, const int index)
{
	return (bb >> index) & 1ULL;
}

void print_bb(U64 bb)
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

static int get_sq_index(const char* sq)
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
static enum PieceType get_piece_type(struct Bitboards *bb, int index)
{
	for (int i = 0; i < TOTAL_BB; i++)
	{
		// bitboard is set at index
		if (get_bit(bb->pieces[i], index))
		{
			// don't need to worry about matching against
			// BLACK_ALL or WHITE_ALL. if it doesn't
			// match against the individual pieces, it
			// won't match against the COLOR_ALL boards
			return i;
		}
	}
	return NONEXISTENT;
}

// piece must exist before calling this func
static int get_piece_color(struct Bitboards *bb, int index)
{
	if (get_bit(bb->pieces[BLACK_ALL], index))
	{
		return BLACK;
	}
	else if (get_bit(bb->pieces[WHITE_ALL], index))
	{
		return WHITE;
	}
	return NONEXISTENT;
}

// validate_command = legal syntax
// parse_move = pseudo-legal
// validate_move = legal

// checks if move is pseudo-legal
// if illegal, return NULL
// if pseudo-legal, return the Move struct ptr
struct Move *parse_move(struct Bitboards *bb, struct Move *move, char *command)
{
	move->start = get_sq_index(command);
	move->end = get_sq_index(command += 2);
	move->piece = get_piece_type(bb, move->start);

	if (move->piece == NONEXISTENT)
	{
		return NULL;
	}

	move->color = get_piece_color(bb, move->start);
	return move;
}
