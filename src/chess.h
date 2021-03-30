/*

I will probably use this later

*/

#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

#include "bitboards.h"
#include "colors.h"
#include "move.h"

// Everything
struct Chess {
	struct Bitboards *bb;
	struct Move *curr;
	struct Move *prev;

	enum Color orient;
	enum Color turn;
	bool ascii;
};

#endif