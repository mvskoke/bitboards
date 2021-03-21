#include <stdbool.h>
#include <stdlib.h>

#include "bitboards.h"
#include "colors.h"
#include "move.h"
#include "validate.h"

bool validate_move(struct Bitboards *bb, struct Move *move, int turn)
{
	// that's not even your piece
	if (turn != move->color)
		return false;
	return true;
}
