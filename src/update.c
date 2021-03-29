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

	// handle castling
	switch (move->type) {
	case W_KINGSIDE_CASTLE:
		// king already moved, just move the rooks
		bb->pretty_board[5][0] = 'R';
		bb->pretty_board[7][0] = EMPTY_SQ;
		break;
	case W_QUEENSIDE_CASTLE:
		bb->pretty_board[3][0] = 'R';
		bb->pretty_board[0][0] = EMPTY_SQ;
		break;
	case B_KINGSIDE_CASTLE:
		bb->pretty_board[5][7] = 'r';
		bb->pretty_board[7][7] = EMPTY_SQ;
		break;
	case B_QUEENSIDE_CASTLE:
		bb->pretty_board[3][7] = 'r';
		bb->pretty_board[0][7] = EMPTY_SQ;
		break;
	default:
		break; // shut up compiler
	}
}

void update_castling(struct Bitboards *bb, struct Move *move)
{
	// actual castling
	switch (move->type) {
	case W_KINGSIDE_CASTLE:
		bb->w_rook_h_moved = true;
		bb->w_king_moved = true;
		return;
	case W_QUEENSIDE_CASTLE:
		bb->w_rook_a_moved = true;
		bb->w_king_moved = true;
		return;
	case B_KINGSIDE_CASTLE:
		bb->b_rook_h_moved = true;
		bb->b_king_moved = true;
		return;
	case B_QUEENSIDE_CASTLE:
		bb->b_rook_a_moved = true;
		bb->b_king_moved = true;
		return;
	default:
		break;
	}

	// ordinary moves
	// white rooks
	if (move->piece == WHITE_ROOKS && move->start == H1)
		bb->w_rook_h_moved = true;
	else if (move->piece == WHITE_ROOKS && move->start == A1)
		bb->w_rook_a_moved = true;
	// black rooks
	else if (move->piece == BLACK_ROOKS && move->start == H8)
		bb->b_rook_h_moved = true;
	else if (move->piece == BLACK_ROOKS && move->start == A8)
		bb->b_rook_a_moved = true;
	// kings
	else if (move->piece == WHITE_KING && move->start == E1)
		bb->w_king_moved = true;
	else if (move->piece == BLACK_KING && move->start == E8)
		bb->b_king_moved = true;
}

// move a piece
// move should be validated BEFORE you call this func
void update_board(struct Bitboards *bb, struct Move *move)
{
	update_pretty_board(bb, move);
	update_castling(bb, move);

	// remove piece from the start...
	flip_bit(&(bb->pieces[move->piece]), move->start);

	// ...and set it on the end
	set_bit(&(bb->pieces[move->piece]), move->end);

	// update COLOR_all bitboards
	if (move->color == WHITE) {
		flip_bit(&(bb->white_all), move->start);
		set_bit(&(bb->white_all), move->end);
	} else {
		flip_bit(&(bb->black_all), move->start);
		set_bit(&(bb->black_all), move->end);
	}

	// handle castling
	switch (move->type) {
	case W_KINGSIDE_CASTLE:
		// king already moved, just move the rooks
		flip_bit(&(bb->pieces[WHITE_ROOKS]), H1);
		set_bit(&(bb->pieces[WHITE_ROOKS]), F1);

		flip_bit(&(bb->white_all), H1);
		set_bit(&(bb->white_all), F1);
		break;

	case W_QUEENSIDE_CASTLE:
		flip_bit(&(bb->pieces[WHITE_ROOKS]), A1);
		set_bit(&(bb->pieces[WHITE_ROOKS]), D1);

		flip_bit(&(bb->white_all), H1);
		set_bit(&(bb->white_all), D1);
		break;

	case B_KINGSIDE_CASTLE:
		flip_bit(&(bb->pieces[BLACK_ROOKS]), H8);
		set_bit(&(bb->pieces[BLACK_ROOKS]), F8);

		flip_bit(&(bb->black_all), H8);
		set_bit(&(bb->black_all), F8);
		break;

	case B_QUEENSIDE_CASTLE:
		flip_bit(&(bb->pieces[BLACK_ROOKS]), A8);
		set_bit(&(bb->pieces[BLACK_ROOKS]), D8);

		flip_bit(&(bb->black_all), A8);
		set_bit(&(bb->black_all), D8);
		break;

	default:
		break; // shut up compiler
	}

	bb->all = bb->white_all | bb->black_all;
}
