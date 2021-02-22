#include <stdbool.h>
#include <stdlib.h>

#include "bitboards.h"
#include "colors.h"

bool validate_move(struct Bitboards *bb, struct Move *move, int turn)
{
	if (turn != move->color)
	{
		return false;
	}
	return true;
}
