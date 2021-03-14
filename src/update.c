#include "bitboards.h"
#include "colors.h"

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
	flip_bit(&(bb->pieces[move->color]), move->start);

	// ...and set it on the end
	set_bit(&(bb->pieces[move->piece]), move->end);
	set_bit(&(bb->pieces[move->color]), move->end);
}

void update_attacks(struct Bitboards *bb)
{
	for (int i = 0; i < TOTAL_ATTACKS; i++)
	{
		// zero out the old attacks
		bb->attacks[i] = 0;
		switch (i)
		{
		;
		}
	}
	//update_pawn_pushes(WHITE);
	//update_pawn_pushes(BLACK);
}
