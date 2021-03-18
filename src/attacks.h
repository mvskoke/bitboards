#ifndef ATTACKS_H
#define ATTACKS_H

#include "bitboards.h"
#include "colors.h"

void update_attacks(struct Bitboards *bb);

//make these static once you transfer back to cchess
U64 pawn_attack(U64 piece, enum Color color);
U64 knight_attack(U64 piece);
U64 king_attack(U64 piece);

#endif