#ifndef ATTACKS_H
#define ATTACKS_H

#include "bitboards.h"

// bit masks
#define NOT_A_FILE 0xFEFEFEFEFEFEFEFE
#define NOT_AB_FILE 0xFCFCFCFCFCFCFCFC
#define NOT_H_FILE 0x7F7F7F7F7F7F7F7F
#define NOT_HG_FILE 0x3F3F3F3F3F3F3F3F

void update_attacks(struct Bitboards *bb);

U64 knight_attack(U64 bb);

#endif