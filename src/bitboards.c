#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitboards.h"
#include "colors.h"

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

U64 clear_bits(U64 *bb)
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
			printf(" ");
		}
	}
	printf("\n\n");
}

struct Bitboards *transfer_bb(struct Bitboards *src, struct Bitboards *dest)
{
	memcpy(dest->pieces, src->pieces, sizeof(U64) * TOTAL_BB);
	memcpy(dest->attacks, src->attacks, sizeof(U64) * TOTAL_ATTACKS);

	dest->white_all = src->white_all;
	dest->black_all = src->black_all;

	dest->w_pawn_pushes = src->w_pawn_pushes;
	dest->b_pawn_pushes = src->b_pawn_pushes;

	// there's no need to copy pretty_board[][]
	// a copy of a Bitboards struct will ONLY ever be used for
	// move validation. the pretty_board is, in that case, useless
	return dest;
}
