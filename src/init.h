#ifndef INIT_H
#define INIT_H

#include "chess.h"
#include "bitboards.h"
#include "move.h"

void verify_safe_malloc(void *ptr);
void init_bb(struct Bitboards *bb);
void init_moves(struct Move *curr_move, struct Move *prev_move);
void init_bb_fen(struct Bitboards *bb, char *fen);

struct Chess *init_chess(void);
void destroy_chess(struct Chess *chess);

#endif