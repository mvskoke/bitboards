#include <stdbool.h>
#include <stdio.h>

#include "bitboards.h"
#include "colors.h"
#include "display.h"

// no newlines in these macros
// you're supposed to use puts() !!!!!
#define BLACK_CURR_TURN  " =>  a   b   c   d   e   f   g   h"
#define BLACK_NOT_TURN   "     a   b   c   d   e   f   g   h"

#define WHITE_CURR_TURN  " =>  h   g   f   e   d   c   b   a"
#define WHITE_NOT_TURN   "     h   g   f   e   d   c   b   a"

// ASCII uses same chars for the top and bottom
#define ASCII_TOP_BOTTOM "   +-------------------------------+"
#define ASCII_ROW        "   ---------------------------------"

//                           |             1            |           2           |           3           |           4           |           5           |           6           |           7           |           8           |
#define UTF8_TOP         "   \u250C\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u252C\u2500\u2500\u2500\u2510"

//                           |                          |                       |                       |                       |                       |                       |                       |                       |
#define UTF8_ROW         "   \u251C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u2524"

//                           |                          |                       |                       |                       |                       |                       |                       |                       |
#define UTF8_BOTTOM      "   \u2514\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2518"

// don't worry, it's supposed to have an extra newline here
#define SMALL_BLACK_TOP "\n      a b c d e f g h\n"
#define SMALL_WHITE_TOP "\n      h g f e d b c a\n"

// use printf with these macros!!!!
#define ASCII_EMPTY_LIGHT "|   "
#define ASCII_EMPTY_DARK  "|***"

#define ASCII_PIECE_LIGHT "| %c "
#define ASCII_PIECE_DARK  "|*%c*"

#define UTF8_EMPTY_LIGHT  "\u2502   "
#define UTF8_EMPTY_DARK   "\u2502***"

#define UTF8_PIECE_LIGHT  "\u2502 %c "
#define UTF8_PIECE_DARK   "\u2502*%c*"

#define ASCII_END         "| %d\n"
#define UTF8_END          "\u2502 %d\n"

static void print_empty_square(int i, int j, bool ascii)
{
	if (ascii && (i+j) % 2 == 0)
		printf(ASCII_EMPTY_DARK);
	else if (ascii && (i+j) % 2 != 0)
		printf(ASCII_EMPTY_LIGHT);
	else if (!ascii && (i+j) % 2 == 0)
		printf(UTF8_EMPTY_DARK);
	else
		printf(UTF8_EMPTY_LIGHT);
}

static void print_piece(struct Bitboards *bb, int i, int j, bool ascii)
{
	// this is solely to make the lines
	// shorter inside the if-statements
	char piece = bb->pretty_board[i][j];

	if (ascii && (i+j) % 2 == 0)
		printf(ASCII_PIECE_DARK, piece);
	else if (ascii && (i+j) % 2 != 0)
		printf(ASCII_PIECE_LIGHT, piece);
	else if (!ascii && (i+j) % 2 == 0)
		printf(UTF8_PIECE_DARK, piece);
	else
		printf(UTF8_PIECE_LIGHT, piece);
}

static void print_black_on_top(struct Bitboards *bb, bool ascii)
{
	// we must start at top row (j coordinate),
	// and go by columns (i coordinate)
	for (int j = 7; j >= 0; j--) {
		printf(" %d ", j+1);
		for (int i = 0; i < FILES; i++) {
			if (bb->pretty_board[i][j] == EMPTY_SQ) {
				print_empty_square(i, j, ascii);
			} else {
				// pass in entire bb instead of just the
				// piece, makes the line length shorter
				print_piece(bb, i, j, ascii);
			}
		}
		// one rank done, close off the squares
		ascii ? printf(ASCII_END, j+1) : printf(UTF8_END, j+1);

		// and print the row border
		// (but not if we're at the last rank)
		// if black is on top, first rank is rank 7
		// so the last rank is rank 0
		if (j != 0) {
			ascii ? puts(ASCII_ROW) : puts(UTF8_ROW);
		}

	}
}

static void print_white_on_top(struct Bitboards *bb, bool ascii)
{
	for (int j = 0; j < RANKS; j++) {
		printf(" %d ", j+1);
		for (int i = 7; i >= 0; i--) {
			if (bb->pretty_board[i][j] == EMPTY_SQ)
				print_empty_square(i, j, ascii);
			else
				print_piece(bb, i, j, ascii);
		}
		ascii ? printf(ASCII_END, j+1) : printf(UTF8_END, j+1);

		// if white is on top, first rank is rank 0
		// so last rank is rank 7
		if (j != 7) {
			ascii ? puts(ASCII_ROW) : puts(UTF8_ROW);
		}
	}
}

void print_bb_pretty(struct Bitboards *bb, int orient, int turn, bool ascii)
{
	// print letters
	if (orient == BLACK && orient == turn)
		puts(BLACK_CURR_TURN);
	else if (orient == BLACK && orient != turn)
		puts(BLACK_NOT_TURN);
	else if (orient == WHITE && orient == turn)
		puts(WHITE_CURR_TURN);
	else
		puts(WHITE_NOT_TURN);

	// print top row border
	ascii ? puts(ASCII_TOP_BOTTOM) : puts(UTF8_TOP);

	// print board
	if (orient == WHITE)
		print_white_on_top(bb, ascii);
	else
		print_black_on_top(bb, ascii);

	// close with bottom row border
	ascii ? puts(ASCII_TOP_BOTTOM) : puts(UTF8_BOTTOM);

	// print letters again
	if (orient == BLACK && orient != turn)
		puts(BLACK_CURR_TURN);
	else if (orient == BLACK && orient == turn)
		puts(BLACK_NOT_TURN);
	else if (orient == WHITE && orient != turn)
		puts(WHITE_CURR_TURN);
	else
		puts(WHITE_NOT_TURN);

}

static void small_black_top(struct Bitboards *bb)
{
	for (int j = 7; j >= 0; j--) {
		printf("   %d ", j+1);

		for (int i = 0; i < FILES; i++)
			printf(" %c", bb->pretty_board[i][j]);

		printf("\n");
	}
	puts(SMALL_BLACK_TOP);
}

static void small_white_top(struct Bitboards *bb)
{
	for (int j = 0; j < RANKS; j++) {
		printf("   %d ", j+1);

		for (int i = 7; i >= 0; i--)
			printf(" %c", bb->pretty_board[i][j]);

		printf("\n");
	}
	puts(SMALL_WHITE_TOP);
}

// special thanks to Oscar Gutierrez Toledo for the
// formatting of this board style
// "Toledo Chess 1" - https://nanochess.org/chess.html
void print_bb_small(struct Bitboards *bb, int orient)
{
	if (orient == WHITE)
		small_white_top(bb);
	else
		small_black_top(bb);
}
