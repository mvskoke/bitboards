#ifndef ATTACKS_H
#define ATTACKS_H

#include "bitboards.h"
#include "colors.h"

enum Ray {
	RAY_NORTHWEST,
	RAY_NORTHEAST,
	RAY_SOUTHWEST,
	RAY_SOUTHEAST,
	RAY_NORTH,
	RAY_EAST,
	RAY_SOUTH,
	RAY_WEST
};

void update_attacks(struct Bitboards *bb);

//make these static once you transfer back to cchess
U64 pawn_attack(U64 piece, U64 self, enum Color color);
U64 pawn_push(U64 pawns, U64 all, enum Color color);
U64 knight_attack(U64 piece, U64 self);
U64 bishop_attack(U64 piece, U64 self, U64 enemy);
U64 rook_attack(U64 piece, U64 self, U64 enemy);
U64 king_attack(U64 piece, U64 self);
U64 queen_attack(U64 piece, U64 self, U64 enemy);

#endif