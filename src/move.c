#include <stdio.h>
#include <stdlib.h>

#include "bitboards.h"
#include "colors.h"
#include "move.h"

static enum Square get_sq_index(const char* sq)
{
	// example:
	// index  0 1
	//    sq "e 2"

	int rank = 8 * (sq[1] - '1');
	// 8 * ('2' - '1')
	// 8 * (50-49)
	// 8 * 1 == 8

	int offset = sq[0] - 'a';
	// 'e' - 'a'
	// 101 - 97 == 4

	// 8 + 4 == 12
	return rank + offset;
}

// you can pass in a move or a single square. it only checks
// the first two chars
static enum Piece get_piece_type(struct Bitboards *bb, int index)
{
	for (int i = 0; i < TOTAL_BB; i++) {
		// bitboard is set at index
		if (get_bit(bb->pieces[i], index))
			return i;
	}
	return NONEXISTENT;
}

// piece must exist before calling this func
static enum Color get_piece_color(struct Bitboards *bb, int index)
{
	if (get_bit(bb->black_all, index))
		return BLACK;
	else if (get_bit(bb->white_all, index))
		return WHITE;
	return NONEXISTENT;
}

static enum Piece parse_promotion(enum Color color, const char* command)
{
	enum Piece promotion;

	// O(1) version of strlen() != 4
	// I know it looks like a ticking time bomb, and that time
	// bomb is a segfault, but a move command will always have
	// an accessible char at index 4.
	if (command[4] != '\0') {
		switch (command[4]) {
		case 'n':
			promotion = BLACK_KNIGHTS;
			break;
		case 'b':
			promotion = BLACK_BISHOPS;
			break;
		case 'r':
			promotion = BLACK_ROOKS;
			break;
		case 'q':
			promotion = BLACK_QUEENS;
			break;
		}
		// use WHITE_PAWNS as an offset between black pieces'
		// and white pieces' enums
		if (color == WHITE)
			promotion += WHITE_PAWNS;
	} else {
		promotion = NONEXISTENT;
	}
	return promotion;
}

static enum MoveType parse_move_type(struct Bitboards *bb, struct Move *move)
{
	if (move->piece == WHITE_KING && move->start == E1 &&
	    move->end == G1)
		return W_KINGSIDE_CASTLE;
	else if (move->piece == WHITE_KING && move->start == E1 &&
	         move->end == C1)
		return W_QUEENSIDE_CASTLE;
	else if (move->piece == BLACK_KING && move->start == E8 &&
	         move->end == G8)
		return B_KINGSIDE_CASTLE;
	else if (move->piece == BLACK_KING && move->start == E8 &&
	         move->end == C8)
		return B_QUEENSIDE_CASTLE;
	else if (get_piece_color(bb, move->end) == !move->color)
		return CAPTURE;
	else
		return OTHER;
}

// validate_command = legal syntax
// parse_move = piece exists
// validate_move = legal

// checks if piece exists
// if illegal, return NULL
// if exists, return the Move struct ptr

// destructive: modifies *move
// encodes a move command into an easy-to-parse form for move validation
struct Move *parse_move(struct Bitboards *bb, struct Move *move, char *const command)
{
	char *tmp = command;
	// I use tmp because I need *command to not change
	// before I parse for a pawn promotion
	move->start = get_sq_index(tmp);
	move->end = get_sq_index(tmp += 2);

	// calculate indexes for pretty_board[][]
	move->start_x = move->start % 8;
	move->start_y = move->start >> 3;  // integer division by 8
	move->end_x   = move->end % 8;
	move->end_y   = move->end >> 3;

	// start parsing the piece in the move
	move->piece = get_piece_type(bb, move->start);
	if (move->piece == NONEXISTENT)
		return NULL;

	move->color = get_piece_color(bb, move->start);

	move->promotion = parse_promotion(move->color, command);

	move->type = parse_move_type(bb, move);

	move->captured = get_piece_type(bb, move->end);

	return move;
}

// transfer current move to previous move
// used after you read a new move. transfer curr to prev, then
// parse the new move into the curr move
struct Move *transfer_move(struct Move *curr, struct Move *prev)
{
	if (curr == NULL || prev == NULL)
		return NULL;

	prev->start = curr->start;
	prev->end = curr->end;
	prev->color = curr->color;
	prev->piece = curr->piece;
	prev->promotion = curr->promotion;
	prev->type = curr->type;

	prev->start_x = curr->start_x;
	prev->end_x = curr->end_x;
	prev->start_y = curr->start_y;
	prev->end_y = curr->end_y;
	return prev;
}
