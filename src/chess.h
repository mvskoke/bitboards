/*

I will probably use this later

I can't really use this in the bitboards repo, because it will
mess up all my prior Unity tests. Make the necessary changes
to all the functions once you go back to cchess.

*/

#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#include "attacks.h"
#include "bitboards.h"
#include "colors.h"
#include "display.h"
#include "init.h"
#include "move.h"
#include "update.h"
#include "validate.h"

// Everything
struct Chess {
	struct Bitboards *bb;
	struct Bitboards *copy;
	struct Move *curr;
	struct Move *prev;

	enum Color orient;
	enum Color turn;
	bool ascii;
};

struct Chess *init_chess(void);
void destroy_chess(struct Chess *chess);

#endif