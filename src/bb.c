#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bb.h"

/* THESE BIT FUNCTIONS RETURN THE MODIFIED BITBOARD
   BECAUSE IT MADE UNITY TESTING EASIER */

uint64_t set_bit(uint64_t *bb, const int index)
{
	*bb |= 1ULL << index;
	return *bb;
}

uint64_t flip_bit(uint64_t *bb, const int index)
{
	*bb ^= 1ULL << index;
	return *bb;
}

uint64_t clear_bb(uint64_t *bb)
{
	*bb = 0;
	return *bb;
}

uint64_t clear_bit(uint64_t *bb, const int index)
{
	// mask out the bit at int index
	// to make mask, xor UINT64_MAX with the mask's complement
	// ...1111111111
	// ...0000000100
	// ...1111111011
	uint64_t mask = UINT64_MAX;
	mask ^= (1ULL << index);
	*bb &= mask;
	return *bb;
}

int get_bit(const uint64_t bb, const int index)
{
	return (bb >> index) & 1ULL;
}

static void print_empty_square(int j, int i)
{
	if ((j%2 == 1) ^ (i%2 == 1))
	{
		printf("|   ");
	}
	else
	{
		printf("|***");
	}
}

static void print_piece(char piece, int j, int i)
{
	if ((j%2 == 1) ^ (i%2 == 1))
	{
		printf("| %c ", piece);
	}
	else
	{
		printf("|*%c*", piece);
	}
	
}

void print_bb_pretty(struct Bitboards *bb, int orient, int turn)
{
	if (orient == turn)
	{
		printf(" =>  a   b   c   d   e   f   g   h\n");
	}
	else
	{
		printf("     a   b   c   d   e   f   g   h\n");
	}
	printf("   +-------------------------------+\n");

	for (int i = 7; i >= 0; i--)
	{
		printf(" %d ", i+1);
		for (int j = 0; j < FILES; j++)
		{
			if (bb->pretty_board[j][i] == EMPTY_SQ)
			{
				print_empty_square(j, i);
			}
			else
			{
				print_piece(bb->pretty_board[j][i], j, i);
			}
		}
		// one rank done
		printf("| %d\n", i+1);
		if (i != 0)
		{
			printf("   ---------------------------------\n");
		}

	}
	printf("   +-------------------------------+\n");

	if (orient != turn)
	{
		printf(" =>  a   b   c   d   e   f   g   h\n");
	}
	else
	{
		printf("     a   b   c   d   e   f   g   h\n");
	}
}

void print_bb_small(struct Bitboards *bb)
{
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < FILES; j++)
		{
			printf(" %c", bb->pretty_board[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void print_bb(uint64_t bb)
{
	int index;
	int curr_bit;
	int i = 0; // file
	int j = 7; // rank
	while (j != -1)
	{
		index = i + 8 * j;
		curr_bit = get_bit(bb, index);
		printf("%i", curr_bit);

		i++;
		if (i == 8)
		{
			i = 0;
			j--;
			printf("\n");
		}
		else
		{
			printf(", ");
		}
	}
	printf("\n\n");
}

void print_all_bb(struct Bitboards *bb)
{
	for (int i = 0; i < TOTAL_BB; i++)
	{
		print_bb(bb->pieces[i]);
		//print_bb(bb->bPieces[i]);
	}
	print_bb(bb->pieces[WHITE_ALL] | bb->pieces[BLACK_ALL]);
}

void verify_safe_malloc(void *ptr)
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

	//                                                                                     7654 3210
	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 1111 1111 | 0000 0000
	bb->pieces[WHITE_PAWNS]      = 0x000000000000FF00;

	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0100 0010
	bb->pieces[WHITE_KNIGHTS]    = 0x0000000000000042;

	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0010 0100
	bb->pieces[WHITE_BISHOPS]    = 0x0000000000000024;

	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 1000 0001
	bb->pieces[WHITE_ROOKS]      = 0x0000000000000081;

	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 1000
	bb->pieces[WHITE_QUEENS]     = 0x0000000000000008;

	// 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0001 0000
	bb->pieces[WHITE_KING]       = 0x0000000000000010;

	bb->pieces[WHITE_ALL]        = 0x000000000000FFFF;

	// for black pieces, move the pawns right by 5 bytes, other pieces by 7 bytes
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

	// 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 0000 0000 / 1010 0101 / 0000 0000 / 0000 0000
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
		if (isdigit(*tmp))
		{
			// convert digit char to int
			index += *tmp - '0';
		}
		if (*tmp == '/')
		{
			rank--;
			index = rank * 8;
		}
	}
}

int get_sq_index(const char* sq)
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
enum PieceType get_piece_type(struct Bitboards *bb, char *move)
{
	int index = get_sq_index(move);
	for (int i = 0; i < TOTAL_BB; i++)
	{
		// bitboard is set at index
		if (bb->pieces[i] & (1ULL << index))
		{
			return i;
		}
	}
	// THIS SHOULD NEVER HAPPEN.
	// YOU SHOULD VALIDATE PIECE EXISTENCE BEFORE CALLING THIS.
	return NONEXISTENT;
}

enum PieceType letter_to_piece_type(char c)
{
	switch (c)
	{
	case 'p': return BLACK_PAWN;
	case 'n': return BLACK_KNIGHT;
	case 'b': return BLACK_BISHOP;
	case 'r': return BLACK_ROOK;
	case 'q': return BLACK_QUEEN;
	case 'k': return BLACK_KING;

	case 'P': return WHITE_PAWN;
	case 'N': return WHITE_KNIGHT;
	case 'B': return WHITE_BISHOP;
	case 'R': return WHITE_ROOK;
	case 'Q': return WHITE_QUEEN;
	case 'K': return WHITE_KING;
	default: return NONEXISTENT;
	}
}

enum PieceType letter_to_color(char c)
{
	switch (c)
	{
	case 'p': return BLACK_ALL;
	case 'n': return BLACK_ALL;
	case 'b': return BLACK_ALL;
	case 'r': return BLACK_ALL;
	case 'q': return BLACK_ALL;
	case 'k': return BLACK_ALL;

	case 'P': return WHITE_ALL;
	case 'N': return WHITE_ALL;
	case 'B': return WHITE_ALL;
	case 'R': return WHITE_ALL;
	case 'Q': return WHITE_ALL;
	case 'K': return WHITE_ALL;
	default: return NONEXISTENT;
	}
}

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
	if (piece < WHITE_PAWN)
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

static void add_to_pretty_board(struct Bitboards *bb, char piece, int index)
{
	// convert bit index to (i,j) index
	int i = index % 8;
	int j = ((index - i) / 8);
	bb->pretty_board[i][j] = piece;
}

void fen_updates_bb(struct Bitboards *bb, char piece, int index)
{
	add_to_pretty_board(bb, piece, index);
	enum PieceType type = letter_to_piece_type(piece);
	enum PieceType color = letter_to_color(piece);
	set_bit(&bb->pieces[type], index);
	set_bit(&bb->pieces[color], index);
}
