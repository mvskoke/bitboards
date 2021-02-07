#ifndef BITBOARDS_H
#define BITBOARDS_H

#include <stdint.h>

enum
{
	BLACK_PAWN,
	BLACK_KNIGHT,
	BLACK_BISHOP,
	BLACK_ROOK,
	BLACK_QUEEN,
	BLACK_KING,
	WHITE_PAWN,
	WHITE_KNIGHT,
	WHITE_BISHOP,
	WHITE_ROOK,
	WHITE_QUEEN,
	WHITE_KING
};

// indexes for the arrays of bitboards
enum
{
	PAWNS,	 // 0
	KNIGHTS, // 1
	BISHOPS, // 2
	ROOKS,	 // 3
	QUEENS,	 // 4
	KING,	 // 5
	ALL,	 // 6 -- the attack bitboards don't use this
	TOTAL_BB // 7
};

struct BitBoards
{
	//char pretty_board[8][8];

	// locations
	uint64_t wPieces[TOTAL_BB];
	uint64_t bPieces[TOTAL_BB];

	// pseudo-legal attacks
	// square is either empty or has enemy piece to capture
	// but unknown if move would leave you in check
	uint64_t wAttacks[TOTAL_BB-1];
	uint64_t bAttacks[TOTAL_BB-1];
};

/* SHOULD PROBABLY ADD bb_ PREFIX WHEN MAKING 
   ACTUAL IMPLEMENTATION FOR cchess */

int set_bit(uint64_t *bb, int index);
int flip_bit(uint64_t *bb, int index);
int clear_bits(uint64_t *bb);
int get_bit(uint64_t bb, int index);

void print_bb(uint64_t bb);

void init_bb(struct BitBoards *bb);
int get_sq_index(char *sq);
void update_bb(struct BitBoards *bb, int piece, int start, int end);

#endif