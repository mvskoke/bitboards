#include <stdbool.h>
#include <stdlib.h>

#include "attacks.h"
#include "bitboards.h"
#include "colors.h"
#include "move.h"
#include "update.h"
#include "validate.h"

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
			return true;
	} else {
		if (get_bit(bb->b_pawn_pushes, move->end))
			return true;
	}
	return false;
}

static bool validate_pawn_capture(struct Bitboards *bb, struct Move *move)
{
	if (move->color == WHITE) {
		// the piece attacks the square, AND
		// there is a piece to capture
		if (get_bit(bb->attacks[WHITE_PAWNS], move->end) &&
		    get_bit(bb->black_all, move->end))
			return true;
	} else {
		if (get_bit(bb->attacks[BLACK_PAWNS], move->end) &&
		    get_bit(bb->white_all, move->end))
			return true;
	}
	return false;
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
	return false;
}

bool legal_dest(struct Bitboards *bb, struct Move *move)
{
	// is your own piece on the end square?
	if (move->color == WHITE) {
		if (get_bit(bb->white_all, move->end))
			return false;
	} else {
		if (get_bit(bb->black_all, move->end))
			return false;
	}
	return true;
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
	U64 squares = (1ULL << sq1) | (1ULL << sq2);

	if (enemy == WHITE) {
		// check the enemy's attacks
		i = WHITE_PAWNS;
		limit = TOTAL_ATTACKS;
	} else {
		i = BLACK_PAWNS;
		limit = WHITE_PAWNS;
	}

	for (; i < limit; i++) {
		if (attacks[i] & squares)
			return false;
	}
	return true;
}

bool clear_path(struct Bitboards *bb, enum Square sq1, enum Square sq2)
{
	U64 squares = (1ULL << sq1) | (1ULL << sq2);
	if (bb->all & squares)
		return false;
	return true;
}

bool validate_castle(struct Bitboards *bb, struct Move *move)
{
	bool legal = false;

	// is castling even legal?
	if (!bb->w_kingside_castle && move->type == W_KINGSIDE_CASTLE)
		return false;
	else if (!bb->w_queenside_castle && move->type == W_QUEENSIDE_CASTLE)
		return false;
	else if (!bb->b_kingside_castle && move->type == B_KINGSIDE_CASTLE)
		return false;
	else if (!bb->b_queenside_castle && move->type == B_QUEENSIDE_CASTLE)
		return false;

	// would the king pass thru check?
	switch (move->type) {
	case W_KINGSIDE_CASTLE:
		legal = safe_path(bb->attacks, BLACK, F1, G1);
		legal &= clear_path(bb, F1, G1);
		break;
	case W_QUEENSIDE_CASTLE:
		legal = safe_path(bb->attacks, BLACK, B1, C1);
		legal &= clear_path(bb, D1, C1);
		break;
	case B_KINGSIDE_CASTLE:
		legal = safe_path(bb->attacks, WHITE, F8, G8);
		legal &= clear_path(bb, F8, G8);
		break;
	case B_QUEENSIDE_CASTLE:
		legal = safe_path(bb->attacks, WHITE, B8, C8);
		legal &= clear_path(bb, B8, C8);
		break;
	default:
		return false;
	}
	return legal;
}

// validates that a move is PSEUDO-LEGAL
bool validate_king_move(struct Bitboards *bb, struct Move *move)
{
	if (move->type != OTHER && move->type != CAPTURE)
		return validate_castle(bb, move);
	else
		return attacks_set(bb, move) && legal_dest(bb, move);
	// REMOVE legal_dest() from this return statement later
	// I added it to make the Unity testing easier
}

// pass into this function a color and determine
// if that color's king is in check
bool king_in_check(struct Bitboards *bb, enum Color color)
{
	enum Piece i;
	enum Piece limit;
	enum Piece king;

	if (color == WHITE)
		king = WHITE_KING;
	else
		king = BLACK_KING;

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

// backup functions in case attacks_set() is inadequate
static bool verify_rook_move(struct Move *move)
{
	bool same_file = move->start_x == move->end_x;
	bool same_rank = move->start_y == move->end_y;
	return same_file ^ same_rank;
}

static bool verify_bishop_move(struct Move *move)
{
	int file_diff = abs(move->end_x - move->start_x);
	int rank_diff = abs(move->end_y - move->start_y);
	return file_diff == rank_diff;
}

static bool verify_queen_move(struct Move *move)
{
	return verify_bishop_move(move) ^ verify_rook_move(move);
}

bool validate_move(struct Bitboards *bb, struct Bitboards *copy,
                   struct Move *move, enum Color turn)
{
	bool pseudo_legal = false;
	bool full_legal = false;

	// that's not even your piece
	if (turn != move->color)
		return false;

	if (!legal_dest(bb, move))
		return false;

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
	case BLACK_BISHOPS:
	case WHITE_BISHOPS:
		pseudo_legal = verify_bishop_move(move);
		pseudo_legal &= attacks_set(bb, move);
		break;
	case BLACK_ROOKS:
	case WHITE_ROOKS:
		pseudo_legal = verify_rook_move(move);
		pseudo_legal &= attacks_set(bb, move);
		break;
	case BLACK_QUEENS:
	case WHITE_QUEENS:
		pseudo_legal = verify_queen_move(move);
		pseudo_legal &= attacks_set(bb, move);
		break;
	default:
		pseudo_legal = attacks_set(bb, move);
		break;
	}

	// would the move put the king in check?
	// first, make sure the copy is up-to-date!!!
	transfer_bb(bb, copy);
	// second, do the move
	update_board(copy, move);
	update_attacks(copy);
	full_legal = !king_in_check(copy, turn);

	return pseudo_legal && full_legal;
}
