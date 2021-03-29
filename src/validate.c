#include <stdbool.h>
#include <stdlib.h>

#include "bitboards.h"
#include "colors.h"
#include "move.h"
#include "validate.h"

#define ILLEGAL false
#define LEGAL true

#define NORTHWEST(index) (index + 7)
#define NORTHEAST(index) (index + 9)
#define SOUTHWEST(index) (index - 9)
#define SOUTHEAST(index) (index - 7)
#define NORTH1(index)    (index + 8)
#define NORTH2(index)    (index + 16)
#define SOUTH1(index)    (index - 8)
#define SOUTH2(index)    (index - 16)

static bool validate_pawn_push(struct Bitboards *bb, struct Move *move)
{
	if (move->color == WHITE) {
		if (get_bit(bb->w_pawn_pushes, move->end))
			return LEGAL;
	} else {
		if (get_bit(bb->b_pawn_pushes, move->end))
			return LEGAL;
	}
	return ILLEGAL;
}

static bool validate_pawn_capture(struct Bitboards *bb, struct Move *move)
{
	if (move->color == WHITE) {
		// the piece attacks the square, AND
		// there is a piece to capture
		if (get_bit(bb->attacks[WHITE_PAWNS], move->end) &&
		    get_bit(bb->black_all, move->end))
			return LEGAL;
	} else {
		if (get_bit(bb->attacks[BLACK_PAWNS], move->end) &&
		    get_bit(bb->white_all, move->end))
			return LEGAL;
	}
	return ILLEGAL;
}

bool validate_pawn_move(struct Bitboards *bb, struct Move *move)
{
	if (move->color == WHITE) {
		if (move->end == NORTH1(move->start) ||
		    move->end == NORTH2(move->start))
			return validate_pawn_push(bb, move);
		else if (move->end == NORTHWEST(move->start) ||
		         move->end == NORTHEAST(move->start))
			return validate_pawn_capture(bb, move);
	} else {
		if (move->end == SOUTH1(move->start) ||
		    move->end == SOUTH2(move->start))
			return validate_pawn_push(bb, move);
		else if (move->end == SOUTHWEST(move->start) ||
		         move->end == SOUTHEAST(move->start))
			return validate_pawn_capture(bb, move);
	}
	return ILLEGAL;
}

bool validate_move(struct Bitboards *bb, struct Move *move, enum Color turn)
{
	// that's not even your piece
	if (turn != move->color)
		return ILLEGAL;

	/* legal destination */
	// is your own piece on the end square?
	if (move->color == WHITE) {
		if (get_bit(bb->white_all, move->end))
			return ILLEGAL;
	} else {
		if (get_bit(bb->black_all, move->end))
			return ILLEGAL;
	}

	// is the end square within reach of the piece?
	switch (move->piece) {
	// pawns and king are special
	case WHITE_PAWNS:
	case BLACK_PAWNS:
		return validate_pawn_move(bb, move);
	case WHITE_KING:
	case BLACK_KING:
		break;
	default:
		break;
	}

	return LEGAL;
}
