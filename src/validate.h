#ifndef VALIDATE_H
#define VALIDATE_H

#include "bitboards.h"
#include "move.h"

bool validate_move(struct Bitboards *bb, struct Move *move, int turn);

#endif