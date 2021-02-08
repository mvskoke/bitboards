#ifndef BITBOARDS_H
#define BITBOARDS_H

#define ROWS 8
#define COLS 8
#define RANKS 8
#define FILES 8

#define BLACK 0
#define WHITE 1

#include <stdint.h>

// indexes for the arrays of bitboards
enum PieceBitboardIndexes
{
	BLACK_PAWN,   // 0 == i
	BLACK_KNIGHT, // 1
	BLACK_BISHOP, // 2
	BLACK_ROOK,   // 3
	BLACK_QUEEN,  // 4
	BLACK_KING,   // 5

	WHITE_PAWN,   // 6 == i+6
	WHITE_KNIGHT, // 7
	WHITE_BISHOP, // 8
	WHITE_ROOK,   // 9
	WHITE_QUEEN,  // 10
	WHITE_KING,   // 11

	BLACK_ALL,
	WHITE_ALL,
	TOTAL_BB
};

// same as above but plural
enum PieceBitboardIndexesPlural
{
	BLACK_PAWNS,
	BLACK_KNIGHTS,
	BLACK_BISHOPS,
	BLACK_ROOKS,
	BLACK_QUEENS,
	DONT_NEED_TO_PLURALIZE_THIS_ENUM1,

	WHITE_PAWNS,
	WHITE_KNIGHTS,
	WHITE_BISHOPS,
	WHITE_ROOKS,
	WHITE_QUEENS
	// we can end here, no need to
	// pluralize the rest
};

struct BitBoards
{
	char pretty_board[8][8];

	// locations
	uint64_t pieces[TOTAL_BB];

	// pseudo-legal attacks
	// square is either empty or has enemy piece to capture
	// but unknown if move would leave you in check
	uint64_t attacks[TOTAL_BB-2];
	// -2 to ignore WHITE_ALL and BLACK_ALL
};

/* SHOULD PROBABLY ADD bb_ PREFIX WHEN MAKING 
   ACTUAL IMPLEMENTATION FOR cchess */

uint64_t set_bit(uint64_t *bb, const int index);
uint64_t flip_bit(uint64_t *bb, const int index);
uint64_t clear_bb(uint64_t *bb);
uint64_t clear_bit(uint64_t *bb, const int index);
int get_bit(const uint64_t bb, const int index);

void print_bb_pretty(struct BitBoards *bb, int orient, int turn);
void print_bb(uint64_t bb);
void print_all_bb(struct BitBoards *bb);

void init_bb(struct BitBoards *bb);
int get_sq_index(const char *sq);
int get_piece_type(struct BitBoards *bb, char *move);
void update_board(struct BitBoards *bb, char *move);

#endif