#ifndef INIT_H
#define INIT_H

#include "bitboards.h"

void init_bb(struct Bitboards *bb);
void init_moves(struct Move *curr_move, struct Move *prev_move);
void init_bb_fen(struct Bitboards *bb, char *fen);

#endif