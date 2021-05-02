#ifndef MATE_H
#define MATE_H

#include "bitboards.h"

int bitscan_forward(U64 bb);
struct Move *gen_move_from_1b(struct Bitboards *bb, struct Move *move_gen,
                              U64 piece, U64 dest);
bool king_has_moves(struct Bitboards *bb, struct Bitboards *copy,
                    struct Move *move_gen, enum Color turn);
bool can_cap_checker(struct Bitboards *bb, struct Bitboards *copy,
                     struct Move *move_gen, enum Color turn, U64 checker);
#endif