#ifndef BITBOARDS_H
#define BITBOARDS_H

#include <stdbool.h>
#include <stdint.h>

#include "colors.h"

// represent empty squares with a period
// in the bitboard's pretty board
#define EMPTY_SQ '.'

// for convenience
typedef uint64_t U64;

// indexing the arrays of bitboards
enum Piece
{
	BLACK_PAWNS,   // 0 = i
	BLACK_KNIGHTS, // 1
	BLACK_BISHOPS, // 2
	BLACK_ROOKS,   // 3
	BLACK_QUEENS,  // 4
	BLACK_KING,    // 5

	WHITE_PAWNS,   // 6 = i+6
	WHITE_KNIGHTS, // 7
	WHITE_BISHOPS, // 8
	WHITE_ROOKS,   // 9
	WHITE_QUEENS,  // 10
	WHITE_KING,    // 11

	TOTAL_BB,      // 12

	TOTAL_ATTACKS = TOTAL_BB,
	NONEXISTENT  // no piece
};

struct Bitboards
{
	// easier to print the board to screen
	char pretty_board[FILES][RANKS];

	// locations
	U64 pieces[TOTAL_BB];
	U64 black_all;
	U64 white_all;

	// pseudo-legal attacks/captures
	// unknown if move would leave you in check
	U64 attacks[TOTAL_ATTACKS];

	// all pieces capture on the same squares on which they
	// move, but the pawn is the only expcetion, so I separate
	// the pawn attacks and pawn pushes (non-captures)
	// might be easier to calculate and validate moves
	U64 w_pawn_pushes;
	U64 b_pawn_pushes;
};

U64 set_bit(U64 *bb, const int index);
U64 flip_bit(U64 *bb, const int index);
U64 clear_bits(U64 *bb);
U64 clear_bit(U64 *bb, const int index);
bool get_bit(const U64 bb, const int index);

void print_bb(U64 bb);

struct Bitboards* transfer_bb(struct Bitboards *src, struct Bitboards *dest);

#endif