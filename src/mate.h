#ifndef MATE_H
#define MATE_H

#include "bitboards.h"

int bitscan_forward(U64 bb);
struct Move *gen_move_from_1b(struct Bitboards *bb, struct Move *move_gen,
                             U64 piece, U64 dest);

#endif