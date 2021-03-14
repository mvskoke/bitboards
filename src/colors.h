#ifndef COLORS_H
#define COLORS_H

// this looks really random, but I promise I have a good reason
enum Color
{
	BLACK = 12,
	WHITE = 13
};
// WHAT: aligns with the indexes of bitboards->pieces (see bitboards.h)
// WHY: makes board updating shorter and a bit more clean (see update.c)
// instead of checking move->color and then accessing the index BLACK_ALL
// or WHITE_ALL, we can just use move->color directly as the index
// the actual value doesn't even matter for anything else, so it's a win-win

#define ROWS 8
#define COLS 8
#define RANKS 8
#define FILES 8

#endif