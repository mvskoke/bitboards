#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "bitboards.h"
#include "colors.h"

// user should have malloc'd memory for struct Bitboards PRIOR
// to calling any of the init functions, and these functions
// will check the malloc'd pointer

static void verify_safe_malloc(void *ptr)
{
	if (ptr == NULL)
	{
		fprintf(stderr, "ERROR: could not allocate enough memory.\n");
		exit(EXIT_FAILURE);
	}
}

void init_moves(struct Move *curr, struct Move *prev)
{
	verify_safe_malloc(curr);
	verify_safe_malloc(prev);

	// dummy placeholder values
	curr->start     = -1;
	curr->end       = -1;
	curr->color     = WHITE;
	curr->piece     = NONEXISTENT;
	curr->promotion = NONEXISTENT;

	curr->start_x   = -1;
	curr->end_x     = -1;
	curr->start_y   = -1;
	curr->end_y     = -1;

	prev->start     = curr->start;
	prev->end       = curr->end;
	prev->color     = curr->color;
	prev->piece     = curr->piece;
	prev->promotion = curr->promotion;

	prev->start_x   = curr->start_x;
	prev->end_x     = curr->end_x;
	prev->start_y   = curr->start_y;
	prev->end_y     = curr->end_y;
}

void init_bb(struct Bitboards *bb)
{
	verify_safe_malloc(bb);

	/**** PIECE LOCATIONS ****/

	//             7654 3210
	// 1111 1111 | 0000 0000
	bb->pieces[WHITE_PAWNS]      = 0x000000000000FF00;

	// 0000 0000 | 0100 0010
	bb->pieces[WHITE_KNIGHTS]    = 0x0000000000000042;

	// 0000 0000 | 0010 0100
	bb->pieces[WHITE_BISHOPS]    = 0x0000000000000024;

	// 0000 0000 | 1000 0001
	bb->pieces[WHITE_ROOKS]      = 0x0000000000000081;

	// 0000 0000 | 0000 1000
	bb->pieces[WHITE_QUEENS]     = 0x0000000000000008;

	// 0000 0000 | 0001 0000
	bb->pieces[WHITE_KING]       = 0x0000000000000010;

	bb->white_all                = 0x000000000000FFFF;

	// for black pieces, move the pawns right by 5 bytes,
	// and other pieces by 7 bytes
	bb->pieces[BLACK_PAWNS]      = 0x00FF000000000000;
	bb->pieces[BLACK_KNIGHTS]    = 0x4200000000000000;
	bb->pieces[BLACK_BISHOPS]    = 0x2400000000000000;
	bb->pieces[BLACK_ROOKS]      = 0x8100000000000000;
	bb->pieces[BLACK_QUEENS]     = 0x0800000000000000;
	bb->pieces[BLACK_KING]       = 0x1000000000000000;
	bb->black_all                = 0xFFFF000000000000;

	/**** PSEUDO-LEGAL ATTACKS ****/

	// we can hardcode these because it's just the setup
	bb->attacks[WHITE_PAWNS]     = 0x0000000000FF0000;

	// 1010 0101 / 0000 0000 / 0000 0000
	bb->attacks[WHITE_KNIGHTS]   = 0x0000000000A50000;

	// you can only move pawns and knights on the first turn
	bb->attacks[WHITE_BISHOPS]   = 0x0000000000000000;
	bb->attacks[WHITE_ROOKS]     = 0x0000000000000000;
	bb->attacks[WHITE_QUEENS]    = 0x0000000000000000;
	bb->attacks[WHITE_KING]      = 0x0000000000000000;

	bb->attacks[BLACK_PAWNS]     = 0x0000FF0000000000;
	bb->attacks[BLACK_KNIGHTS]   = 0x0000A50000000000;
	bb->attacks[BLACK_BISHOPS]   = 0x0000000000000000;
	bb->attacks[BLACK_ROOKS]     = 0x0000000000000000;
	bb->attacks[BLACK_QUEENS]    = 0x0000000000000000;
	bb->attacks[BLACK_KING]      = 0x0000000000000000;

	/**** PRETTY BOARD ****/
	// pretty_board[i][j]
	// i = file a-h, j = rank 1-8

	// initialize empty squares to a period
	// solely for the sake of print_bb_small()
	for (int i = 0; i < FILES; i++)
	{
		for (int j = 2; j <= 5; j++)
			bb->pretty_board[i][j] = EMPTY_SQ;
	}

	for (int i = 0; i < 8; i++)
	{
		bb->pretty_board[i][1] = 'P';
		bb->pretty_board[i][6] = 'p';
	}

	bb->pretty_board[0][0] = 'R';
	bb->pretty_board[0][7] = 'r';

	bb->pretty_board[1][0] = 'N';
	bb->pretty_board[1][7] = 'n';

	bb->pretty_board[2][0] = 'B';
	bb->pretty_board[2][7] = 'b';

	bb->pretty_board[3][0] = 'Q';
	bb->pretty_board[3][7] = 'q';

	bb->pretty_board[4][0] = 'K';
	bb->pretty_board[4][7] = 'k';

	bb->pretty_board[5][0] = 'B';
	bb->pretty_board[5][7] = 'b';

	bb->pretty_board[6][0] = 'N';
	bb->pretty_board[6][7] = 'n';

	bb->pretty_board[7][0] = 'R';
	bb->pretty_board[7][7] = 'r';
}

static void init_bb_blank(struct Bitboards *bb)
{
	verify_safe_malloc(bb);

	// initialize bitboards: pieces and attacks
	for (int i = 0; i < TOTAL_BB; i++)
		bb->pieces[i] = 0;

	for (int i = 0; i < TOTAL_ATTACKS; i++)
		bb->attacks[i] = 0;

	// initialize bitboards of COLOR_all
	bb->white_all = 0;
	bb->black_all = 0;

	// initialize pretty board
	for (int i = 0; i < FILES; i++)
	{
		for (int j = 0; j < RANKS; j++)
			bb->pretty_board[i][j] = EMPTY_SQ;
	}
}

static enum Piece letter_to_piece_type(char c)
{
	switch (c)
	{
	case 'p': return BLACK_PAWNS;
	case 'n': return BLACK_KNIGHTS;
	case 'b': return BLACK_BISHOPS;
	case 'r': return BLACK_ROOKS;
	case 'q': return BLACK_QUEENS;
	case 'k': return BLACK_KING;

	case 'P': return WHITE_PAWNS;
	case 'N': return WHITE_KNIGHTS;
	case 'B': return WHITE_BISHOPS;
	case 'R': return WHITE_ROOKS;
	case 'Q': return WHITE_QUEENS;
	case 'K': return WHITE_KING;
	default: return NONEXISTENT;
	}
}

static void add_to_pretty_board(struct Bitboards *bb, char piece, int index)
{
	// convert bit index to (i,j) index
	int i = index % 8;
	int j = ((index - i) / 8);
	bb->pretty_board[i][j] = piece;
}


// function expects a valid piece!!!
static void fen_updates_bb(struct Bitboards *bb, char piece, int index)
{
	add_to_pretty_board(bb, piece, index);
	enum Piece type = letter_to_piece_type(piece);

	// set specific piece...
	set_bit(&bb->pieces[type], index);

	// and the piece's color
	if (islower(piece))
		set_bit(&bb->black_all, index);
	else
		set_bit(&bb->white_all, index);
}


void init_bb_fen(struct Bitboards *bb, char fen[])
{
	init_bb_blank(bb);
	int index = 56; // MUST BE ZERO-INDEXED TO ALLOW EASY BIT-SETTING
	int rank = 7;

	for (char *tmp = fen; *tmp != '\0'; tmp++)
	{
		if (isalpha(*tmp))
		{
			fen_updates_bb(bb, *tmp, index);
			index++;
		}
		else if (isdigit(*tmp))
		{
			// convert digit char to int
			index += *tmp - '0';
		}
		else if (*tmp == '/')
		{
			rank--;
			index = rank * 8;
		}
	}
}
