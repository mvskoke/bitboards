#include "bitboards.h"
#include "colors.h"

static void update_pretty_board(struct Bitboards *bb, int start, int end)
{
	int start_i = start % 8;
	int start_j = (start - start_i) / 8;

	int end_i = end % 8;
	int end_j = (end - end_i) / 8;
	bb->pretty_board[end_i][end_j] = bb->pretty_board[start_i][start_j];
	bb->pretty_board[start_i][start_j] = EMPTY_SQ;
}

// move a piece
// move should be validated BEFORE you call this func
void update_board(struct Bitboards *bb, struct Move *move)
{
	update_pretty_board(bb, move->start, move->end);

	if (move->color == BLACK)
	{
		flip_bit(&(bb->pieces[move->piece]), move->start);
		flip_bit(&(bb->pieces[BLACK_ALL]),   move->start);
		set_bit( &(bb->pieces[move->piece]), move->end);
		set_bit( &(bb->pieces[BLACK_ALL]),   move->end);
	}
	else
	{
		flip_bit(&(bb->pieces[move->piece]), move->start);
		flip_bit(&(bb->pieces[WHITE_ALL]),   move->start);
		set_bit( &(bb->pieces[move->piece]), move->end);
		set_bit( &(bb->pieces[WHITE_ALL]),   move->end);
	}
}

void update_attacks(struct Bitboards *bb)
{
	// zero out the old attacks
	for (int i = 0; i < TOTAL_ATTACKS; i++)
	{
		bb->attacks[i] = 0;
		// TO DO
	}
}
