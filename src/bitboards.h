#ifndef BITBOARDS_H
#define BITBOARDS_H

#include <stdbool.h>
#include <stdint.h>

#include "colors.h"

// represent empty squares with a period
// in the bitboard's pretty board
#define EMPTY_SQ '.'

// for convenience
#define U64 uint64_t

// indexing the arrays of bitboards
enum PieceType
{
	BLACK_PAWNS,   // 0 == i
	BLACK_KNIGHTS, // 1
	BLACK_BISHOPS, // 2
	BLACK_ROOKS,   // 3
	BLACK_QUEENS,  // 4
	BLACK_KING,    // 5

	WHITE_PAWNS,   // 6 == i+6
	WHITE_KNIGHTS, // 7
	WHITE_BISHOPS, // 8
	WHITE_ROOKS,   // 9
	WHITE_QUEENS,  // 10
	WHITE_KING,    // 11

	BLACK_ALL,     // 12
	WHITE_ALL,     // 13
	TOTAL_BB,      // 14

	// -2 to ignore WHITE_ALL and BLACK_ALL
	TOTAL_ATTACKS = TOTAL_BB-2,
	NONEXISTENT = 15 // no piece
};

struct Bitboards
{
	char pretty_board[FILES][RANKS];

	// locations
	U64 pieces[TOTAL_BB];

	// pseudo-legal attacks
	// square is either empty or has enemy piece to capture
	// but unknown if move would leave you in check
	U64 attacks[TOTAL_ATTACKS];
};

U64 set_bit(U64 *bb, const int index);
U64 flip_bit(U64 *bb, const int index);
U64 clear_bb(U64 *bb);
U64 clear_bit(U64 *bb, const int index);
bool get_bit(const U64 bb, const int index);

void print_bb(U64 bb);

#endif