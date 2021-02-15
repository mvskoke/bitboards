#ifndef DISPLAY_H
#define DISPLAY_H

// no newlines in these macros
// you're supposed to use puts() !!!!!
#define BLACK_CURR_TURN  " =>  a   b   c   d   e   f   g   h"
#define BLACK_NOT_TURN   "     a   b   c   d   e   f   g   h"

#define WHITE_CURR_TURN  " =>  h   g   f   e   d   c   b   a"
#define WHITE_NOT_TURN   "     h   g   f   e   d   c   b   a"

// ASCII uses same chars for the top and bottom
#define ASCII_TOP_BOTTOM "   +-------------------------------+"
#define ASCII_ROW        "   ---------------------------------"

#define UTF8_TOP         "   ┌───┬───┬───┬───┬───┬───┬───┬───┐"

#define UTF8_ROW         "   ├───┼───┼───┼───┼───┼───┼───┼───┤"

#define UTF8_BOTTOM      "   └───┴───┴───┴───┴───┴───┴───┴───┘"

// there's supposed to be an extra newline here
#define SMALL_BOARD_LETTERS "\n      a b c d e f g h\n"


// use printf with string-formatted macros
#define ASCII_EMPTY_LIGHT "|   "
#define ASCII_EMPTY_DARK  "|***"

#define ASCII_PIECE_LIGHT "| %c "
#define ASCII_PIECE_DARK  "|*%c*"

#define UTF8_EMPTY_LIGHT  "│   "
#define UTF8_EMPTY_DARK   "│***"

#define UTF8_PIECE_LIGHT  "│ %c "
#define UTF8_PIECE_DARK   "│*%c*"

#define ASCII_END         "| %d\n"
#define UTF8_END          "│ %d\n"


void print_bb_pretty(struct Bitboards *bb, int orient, int turn, bool ascii);
void print_bb_small(struct Bitboards *bb);

#endif