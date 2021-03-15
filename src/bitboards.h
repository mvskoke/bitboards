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

// little endian rank-file mapping
/*

STILL NEED TO TEST THIS!!!

*/
enum Square
{
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8
};

// indexing the arrays of bitboards
enum Piece
{
	BLACK_PAWNS,   // 1 = i
	BLACK_KNIGHTS, // 2
	BLACK_BISHOPS, // 3
	BLACK_ROOKS,   // 4
	BLACK_QUEENS,  // 5
	BLACK_KING,    // 6

	WHITE_PAWNS,   // 7 = i+6
	WHITE_KNIGHTS, // 8
	WHITE_BISHOPS, // 9
	WHITE_ROOKS,   // 10
	WHITE_QUEENS,  // 11
	WHITE_KING,    // 12

	TOTAL_BB,      // 13

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
	//U64 wpawn_pushes;
	//U64 bpawn_pushes;
};

struct Move
{
	enum Square start;
	enum Square end;
	enum Color color;
	enum Piece piece;
	enum Piece promotion;

	// indexes for Bitboards->pretty_board[][]
	int start_x;
	int start_y;
	int end_x;
	int end_y;
};

// everything
// do i need this???
// struct Chess
// {
// 	struct Bitboards *bb;
// 	struct Move *curr;
// 	struct Move *prev;
// 	enum Color turn;
// 	enum Color orient;
// 	bool ascii;
// }

U64 set_bit(U64 *bb, const int index);
U64 flip_bit(U64 *bb, const int index);
U64 clear_bits(U64 *bb);
U64 clear_bit(U64 *bb, const int index);
bool get_bit(const U64 bb, const int index);

void print_bb(U64 bb);

struct Bitboards* transfer_bb(struct Bitboards *src, struct Bitboards *dest);

struct Move *parse_move(struct Bitboards *bb, struct Move *move, char *command);
void display_move(struct Move *move);
struct Move *transfer_move(struct Move *curr, struct Move *prev);

#endif