#ifndef VALIDATE_H
#define VALIDATE_H

#include <stdbool.h>

#include "bitboards.h"
#include "move.h"

/* make these helpers static when you move back to cchess */
// THESE HELPERS ONLY VALIDATE PSEUDO-LEGAL MOVES!!!
bool validate_pawn_move(struct Bitboards *bb, struct Move *move);
bool attacks_set(struct Bitboards *bb, struct Move *move);
bool safe_path(U64 attacks[], enum Color enemy,
               enum Square sq1, enum Square sq2);
bool validate_castle(struct Bitboards *bb, struct Move *move);
bool validate_king_move(struct Bitboards *bb, struct Move *move);
bool king_in_check(struct Bitboards *bb, enum Color color);

bool validate_move(struct Bitboards *bb, struct Bitboards *copy,
                   struct Move *move, enum Color turn);

#endif