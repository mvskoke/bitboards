#ifndef DISPLAY_H
#define DISPLAY_H

// no newlines in these macros
// you're supposed to use puts() !!!!!
#define CURR_TURN        " =>  a   b   c   d   e   f   g   h"
#define NOT_TURN         "     a   b   c   d   e   f   g   h"

// ASCII uses same chars for the top and bottom
#define ASCII_TOP_BOTTOM "   +-------------------------------+"
#define ASCII_ROW        "   ---------------------------------"

#define UTF8_TOP         "   ┌───┬───┬───┬───┬───┬───┬───┬───┐"

#define UTF8_ROW         "   ├───┼───┼───┼───┼───┼───┼───┼───┤"

#define UTF8_BOTTOM      "   └───┴───┴───┴───┴───┴───┴───┴───┘"

// there's supposed to be an extra newline here
#define SMALL_LETTERS "\n      a b c d e f g h\n"


#define ASCII_EMPTY_LIGHT "|   "
#define ASCII_EMPTY_DARK  "|***"

#define ASCII_PIECE_LIGHT "| %c "
#define ASCII_PIECE_DARK  "|*%c*"

#define UTF8_EMPTY_LIGHT "│   "
#define UTF8_EMPTY_DARK  "│***"

#define UTF8_PIECE_LIGHT "│ %c "
#define UTF8_PIECE_DARK  "│*%c*"

#define ASCII_END "| %d\n"
#define UTF8_END  "│ %d\n"

void print_bb_pretty(struct Bitboards *bb, int orient, int turn, bool ascii);
void print_bb_small(struct Bitboards *bb);

#endif