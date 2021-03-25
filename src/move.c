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
	for (int i = 0; i < TOTAL_BB; i++)
	{
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
	// before the switch statement further down
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

	// O(1) version of strlen() != 4
	// I know it looks like a ticking time bomb, and that time
	// bomb is a segfault, but a move command will always have
	// an accessible char at index 4.
	if (command[4] != '\0')
	{
		switch (command[4])
		{
		case 'n':
			move->promotion = BLACK_KNIGHTS;
			break;
		case 'b':
			move->promotion = BLACK_BISHOPS;
			break;
		case 'r':
			move->promotion = BLACK_ROOKS;
			break;
		case 'q':
			move->promotion = BLACK_QUEENS;
			break;
		}
		// use WHITE_PAWNS as an offset between black pieces'
		// and white pieces' enums
		if (move->color == WHITE)
			move->promotion += WHITE_PAWNS;
	}
	else
	{
		move->promotion = NONEXISTENT;
	}
	return move;
}

// just for debugging
void display_move(struct Move *move)
{
	switch (move->piece)
	{
	case BLACK_PAWNS:       printf("BLACK_PAWN "); break;
	case BLACK_KNIGHTS:     printf("BLACK_KNIGHT "); break;
	case BLACK_BISHOPS:     printf("BLACK_BISHOP "); break;
	case BLACK_ROOKS:       printf("BLACK_ROOK "); break;
	case BLACK_QUEENS:      printf("BLACK_QUEEN "); break;
	case BLACK_KING:        printf("BLACK_KING "); break;
	case WHITE_PAWNS:       printf("WHITE_PAWN "); break;
	case WHITE_KNIGHTS:     printf("WHITE_KNIGHT "); break;
	case WHITE_BISHOPS:     printf("WHITE_BISHOP "); break;
	case WHITE_ROOKS:       printf("WHITE_ROOK "); break;
	case WHITE_QUEENS:      printf("WHITE_QUEEN "); break;
	case WHITE_KING:        printf("WHITE_KING "); break;
	case NONEXISTENT:       printf("STILL INITIALIZED "); break;
	default: break;  // shut up compiler
	}
	printf(" (%c, %i) >", move->start_x + 'a', move->start_y + 1);
	printf(" (%c, %i)\n", move->end_x + 'a', move->end_y + 1);
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

	prev->start_x = curr->start_x;
	prev->end_x = curr->end_x;
	prev->start_y = curr->start_y;
	prev->end_y = curr->end_y;
	return prev;
}
