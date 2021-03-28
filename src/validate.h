#ifndef VALIDATE_H
#define VALIDATE_H

#include <stdbool.h>

#include "bitboards.h"
#include "move.h"

/* make these helpers static when you move back to cchess */
bool validate_pawn_move(struct Bitboards *bb, struct Move *move);

bool validate_move(struct Bitboards *bb, struct Move *move, enum Color turn);

#endif