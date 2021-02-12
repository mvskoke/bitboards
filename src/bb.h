#ifndef BITBOARDS_H
#define BITBOARDS_H

#define ROWS 8
#define COLS 8
#define RANKS 8
#define FILES 8

#define BLACK 0
#define WHITE 1

// represent empty squares with a period
// in the bitboard's pretty board
#define EMPTY_SQ '.'

#define U64 uint64_t

#include <stdint.h>

// indexing the arrays of bitboards of pieces
enum PieceType
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
	TOTAL_BB,
	NONEXISTENT  // no piece
};

#define TOTAL_ATTACKS TOTAL_BB-2

// same as above but plural
// and used for indexing the arrays of bitboards of attacks
enum PieceBBIndex
{
	BLACK_PAWNS = BLACK_PAWN,
	BLACK_KNIGHTS = BLACK_KNIGHT,
	BLACK_BISHOPS = BLACK_BISHOP,
	BLACK_ROOKS = BLACK_ROOK,
	BLACK_QUEENS = BLACK_QUEEN,
	// don't need a BLACK_KINGS

	WHITE_PAWNS = WHITE_PAWN,
	WHITE_KNIGHTS = WHITE_KNIGHT,
	WHITE_BISHOPS = WHITE_BISHOP,
	WHITE_ROOKS = WHITE_ROOK,
	WHITE_QUEENS = WHITE_QUEEN,
	// we can end here, no need to
	// pluralize the rest
};

struct Bitboards
{
	char pretty_board[FILES][RANKS];

	// locations
	U64 pieces[TOTAL_BB];

	// pseudo-legal attacks
	// square is either empty or has enemy piece to capture
	// but unknown if move would leave you in check
	U64 attacks[TOTAL_BB-2];
	// -2 to ignore WHITE_ALL and BLACK_ALL
};

/* SHOULD PROBABLY ADD bb_ PREFIX WHEN MAKING 
   ACTUAL IMPLEMENTATION FOR cchess */

U64 set_bit(U64 *bb, const int index);
U64 flip_bit(U64 *bb, const int index);
U64 clear_bb(U64 *bb);
U64 clear_bit(U64 *bb, const int index);
int get_bit(const U64 bb, const int index);

void print_bb_pretty(struct Bitboards *bb, int orient, int turn);
void print_bb_small(struct Bitboards *bb);
void print_bb(U64 bb);
void print_all_bb(struct Bitboards *bb);

void init_bb(struct Bitboards *bb);
void init_bb_fen(struct Bitboards *bb, char fen[]);

int get_sq_index(const char *sq);
enum PieceType get_piece_type(struct Bitboards *bb, char *move);
enum PieceType letter_to_piece_type(char c);

void update_board(struct Bitboards *bb, char *move);
void fen_updates_bb(struct Bitboards *bb, char piece, int index);

#endif