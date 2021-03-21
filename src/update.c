#include "bitboards.h"
#include "colors.h"
#include "move.h"
#include "update.h"

static void update_pretty_board(struct Bitboards *bb, struct Move *move)
{
	// I declare this char to make the line shorter
	char src = bb->pretty_board[move->start_x][move->start_y];

	// copy piece to the destination square
	bb->pretty_board[move->end_x][move->end_y] = src;
	// and remove the piece from its original square
	bb->pretty_board[move->start_x][move->start_y] = EMPTY_SQ;
}

// move a piece
// move should be validated BEFORE you call this func
void update_board(struct Bitboards *bb, struct Move *move)
{
	update_pretty_board(bb, move);

	// remove piece from the start...
	flip_bit(&(bb->pieces[move->piece]), move->start);

	// ...and set it on the end
	set_bit(&(bb->pieces[move->piece]), move->end);

	// update COLOR_all bitboards
	if (move->color == WHITE)
	{
		flip_bit(&(bb->white_all), move->start);
		set_bit(&(bb->white_all), move->end);
	}
	else
	{
		flip_bit(&(bb->black_all), move->start);
		set_bit(&(bb->black_all), move->end);
	}
}
