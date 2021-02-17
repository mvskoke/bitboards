#include "bitboards.h"
#include "colors.h"

static int get_sq_index(const char* sq)
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
static enum PieceType get_piece_type(struct Bitboards *bb, char *move)
{
	int index = get_sq_index(move);
	for (int i = 0; i < TOTAL_BB; i++)
	{
		// bitboard is set at index
		if (get_bit(bb->pieces[i], index))
		{
			// don't need to worry about matching against
			// BLACK_ALL or WHITE_ALL. if it doesn't
			// match against the individual pieces, it
			// won't match against the COLOR_ALL boards
			return i;
		}
	}
	return NONEXISTENT;
}

// static int get_piece_color(struct Bitboards *bb, char *move)
// {
// 	int index = get_sq_index(move);
// 	if (get_bit(bb->pieces[BLACK_ALL], index))
// 	{
// 		return BLACK;
// 	}
// 	else if (get_bit(bb->pieces[WHITE_ALL], index))
// 	{
// 		return WHITE;
// 	}
// 	return NONEXISTENT;
// }

// update pretty board AFTER A MOVE
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
void update_board(struct Bitboards *bb, char* move)
{
	enum PieceType piece = get_piece_type(bb, move);
	int start = get_sq_index(move);
	int end = get_sq_index(move+=2);
	int color;

	// pieces are sorted black to white, pawn to king
	if (piece < WHITE_PAWNS)
	{
		color = BLACK;
	}
	else
	{
		color = WHITE;
	}
	update_pretty_board(bb, start, end);

	if (color == BLACK)
	{
		flip_bit(&(bb->pieces[piece]), start);
		flip_bit(&(bb->pieces[BLACK_ALL]), start);
		set_bit(&(bb->pieces[piece]), end);
		set_bit(&(bb->pieces[BLACK_ALL]), end);
	}
	else
	{
		flip_bit(&(bb->pieces[piece]), start);
		flip_bit(&(bb->pieces[WHITE_ALL]), start);
		set_bit(&(bb->pieces[piece]), end);
		set_bit(&(bb->pieces[WHITE_ALL]), end);
	}
}
