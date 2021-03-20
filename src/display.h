#ifndef DISPLAY_H
#define DISPLAY_H

#include "bitboards.h"

void print_bb_pretty(struct Bitboards *bb, int orient, int turn, bool ascii);
void print_bb_small(struct Bitboards *bb, int orient);

#endif