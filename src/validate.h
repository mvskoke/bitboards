#ifndef VALIDATE_H
#define VALIDATE_H

#include <stdbool.h>

#include "attacks.h"
#include "bitboards.h"
#include "move.h"

/* make these helpers static when you move back to cchess */
bool validate_pawn_move(struct Bitboards *bb, struct Move *move);
bool attacks_set(struct Bitboards *bb, struct Move *move);
bool safe_path(U64 attacks[], enum Color enemy,
               enum Square sq1, enum Square sq2);
bool clear_path(struct Bitboards *bb, enum Square sq1, enum Square sq2);
bool validate_castle(struct Bitboards *bb, struct Move *move);
bool validate_king_move(struct Bitboards *bb, struct Move *move);
bool king_in_check(struct Bitboards *bb, enum Color color);
bool blocked_path(struct Bitboards *bb, struct Move *move, enum Ray ray);
enum Ray calc_ray(struct Move *move);
bool blocked_sliding_piece(struct Bitboards *bb, struct Move *move);

bool validate_move(struct Bitboards *bb, struct Bitboards *copy,
                   struct Move *move, enum Color turn);

#endif