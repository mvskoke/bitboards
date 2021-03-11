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

//                           |                          |                       |                       |                       |                       |                       |                       |                       |
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


void print_bb_pretty(struct Bitboards *bb, int orient, int turn, bool ascii);
void print_bb_small(struct Bitboards *bb, int orient);

#endif