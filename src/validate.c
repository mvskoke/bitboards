#include <stdbool.h>

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

bool legal_dest(struct Bitboards *bb, struct Move *move)
{
	// is your own piece on the end square?
	if (move->color == WHITE) {
		if (get_bit(bb->white_all, move->end))
			return ILLEGAL;
	} else {
		if (get_bit(bb->black_all, move->end))
			return ILLEGAL;
	}
	return LEGAL;
}

// is the piece's attack bb set on the destination square bit?
bool attacks_set(struct Bitboards *bb, struct Move *move)
{
	return get_bit(bb->attacks[move->piece], move->end);
}

bool safe_path(U64 attacks[], enum Color enemy,
               enum Square sq1, enum Square sq2)
{
	enum Piece i;
	enum Piece limit;
	if (enemy == WHITE) {
		// check the enemy's attacks
		i = WHITE_PAWNS;
		limit = TOTAL_ATTACKS;
	} else {
		i = BLACK_PAWNS;
		limit = WHITE_PAWNS;
	}

	for (; i < limit; i++) {
		if (get_bit(attacks[i], sq1) || get_bit(attacks[i], sq2))
			return ILLEGAL;
	}
	return LEGAL;
}

bool validate_castle(struct Bitboards *bb, struct Move *move)
{
	// is castling legal?
	if (!bb->w_kingside_castle && move->type == W_KINGSIDE_CASTLE)
		return ILLEGAL;
	else if (!bb->w_queenside_castle && move->type == W_QUEENSIDE_CASTLE)
		return ILLEGAL;
	else if (!bb->b_kingside_castle && move->type == B_KINGSIDE_CASTLE)
		return ILLEGAL;
	else if (!bb->b_queenside_castle && move->type == B_QUEENSIDE_CASTLE)
		return ILLEGAL;

	// would the king pass thru check?
	switch (move->type) {
	case W_KINGSIDE_CASTLE:
		return safe_path(bb->attacks, BLACK, F1, G1);
	case W_QUEENSIDE_CASTLE:
		return safe_path(bb->attacks, BLACK, B1, C1);
	case B_KINGSIDE_CASTLE:
		return safe_path(bb->attacks, WHITE, F8, G8);
	case B_QUEENSIDE_CASTLE:
		return safe_path(bb->attacks, WHITE, B8, C8);
	default:
		return ILLEGAL;
	}
}

// validates that a move is PSEUDO-LEGAL
bool validate_king_move(struct Bitboards *bb, struct Move *move)
{
	if (move->type != OTHER)
		return validate_castle(bb, move);
	else
		return (attacks_set(bb, move) && legal_dest(bb, move));
	// REMOVE legal_dest() from this return statement later
	// I added it to make the Unity testing easier
}

// pass into this function a king and determine if that king
// is in check
bool king_in_check(struct Bitboards *bb, enum Piece king)
{
	enum Piece i;
	enum Piece limit;
	if (king == BLACK_KING) {
		// check the enemy's attacks
		// black king means white enemy
		i = WHITE_PAWNS;
		limit = TOTAL_ATTACKS;
	} else {
		i = BLACK_PAWNS;
		limit = WHITE_PAWNS;
	}

	for (; i < limit; i++) {
		if (bb->attacks[i] & bb->pieces[king])
			return true;
	}
	return false;
}

bool validate_move(struct Bitboards *bb, struct Move *move, enum Color turn)
{
	bool pseudo_legal = false;
	bool full_legal = false;

	// that's not even your piece
	if (turn != move->color)
		return ILLEGAL;

	/* legal destination */
	if (!legal_dest(bb, move))
		return ILLEGAL;

	// is the end square within reach of the piece?
	switch (move->piece) {
	// pawns and king are special
	case WHITE_PAWNS:
	case BLACK_PAWNS:
		pseudo_legal = validate_pawn_move(bb, move);
		break;
	case WHITE_KING:
	case BLACK_KING:
		pseudo_legal = validate_king_move(bb, move);
		break;
	default:
		pseudo_legal = attacks_set(bb, move);
		break;
	}

	// update_board(copy, move);
	// update_attacks(copy);
	// full_legal = !king_in_check(copy, turn);
	return pseudo_legal && full_legal;
}
