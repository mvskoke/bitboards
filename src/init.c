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

	bb->pieces[WHITE_ALL]        = 0x000000000000FFFF;

	// for black pieces, move the pawns right by 5 bytes,
	// and other pieces by 7 bytes
	bb->pieces[BLACK_PAWNS]      = 0x00FF000000000000;
	bb->pieces[BLACK_KNIGHTS]    = 0x4200000000000000;
	bb->pieces[BLACK_BISHOPS]    = 0x2400000000000000;
	bb->pieces[BLACK_ROOKS]      = 0x8100000000000000;
	bb->pieces[BLACK_QUEENS]     = 0x0800000000000000;
	bb->pieces[BLACK_KING]       = 0x1000000000000000;
	bb->pieces[BLACK_ALL]        = 0xFFFF000000000000;

	/**** PSEUDO-LEGAL ATTACKS ****/

	// we can hardcode these because it's just the setup
	bb->attacks[WHITE_PAWNS]     = 0x00000000FFFF0000;

	// 1010 0101 / 0000 0000 / 0000 0000
	bb->attacks[WHITE_KNIGHTS]   = 0x0000000000A50000;

	// you can only move pawns and knights on the first turn
	bb->attacks[WHITE_BISHOPS]   = 0x0000000000000000;
	bb->attacks[WHITE_ROOKS]     = 0x0000000000000000;
	bb->attacks[WHITE_QUEENS]    = 0x0000000000000000;
	bb->attacks[WHITE_KING]      = 0x0000000000000000;

	bb->attacks[BLACK_PAWNS]     = 0x0000FFFF00000000;
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
		{
			bb->pretty_board[i][j] = EMPTY_SQ;
		}
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
	{
		bb->pieces[i] = 0;
	}

	for (int i = 0; i < TOTAL_ATTACKS; i++)
	{
		bb->attacks[i] = 0;
	}

	// initialize pretty board
	for (int i = 0; i < FILES; i++)
	{
		for (int j = 0; j < RANKS; j++)
		{
			bb->pretty_board[i][j] = EMPTY_SQ;
		}
	}
}

static enum PieceType letter_to_piece_type(char c)
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
	enum PieceType type = letter_to_piece_type(piece);

	// set specific piece...
	set_bit(&bb->pieces[type], index);

	// and the piece's color
	if (islower(piece))
	{
		set_bit(&bb->pieces[BLACK_ALL], index);
	}
	else
	{
		set_bit(&bb->pieces[WHITE_ALL], index);
	}
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
