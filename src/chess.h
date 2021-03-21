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
struct Chess
{
	struct Bitboards *bb;
	struct Move *curr;
	struct Move *prev;
	enum Color turn;

	enum Color orient;
	bool ascii;

	bool w_queenside_castle;
	bool w_kingside_castle;
	bool b_queenside_castle;
	bool b_kingside_castle;
};

#endif