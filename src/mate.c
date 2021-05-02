#include <stdbool.h>
#include <stdlib.h>

#include "bitboards.h"
#include "colors.h"
#include "mate.h"
#include "move.h"
#include "validate.h"

const int lsb_64_table[64] =
{
	63, 30,  3, 32, 59, 14, 11, 33,
	60, 24, 50,  9, 55, 19, 21, 34,
	61, 29,  2, 53, 51, 23, 41, 18,
	56, 28,  1, 43, 46, 27,  0, 35,
	62, 31, 58,  4,  5, 49, 54,  6,
	15, 52, 12, 40,  7, 42, 45, 16,
	25, 57, 48, 13, 10, 39,  8, 44,
	20, 47, 38, 22, 17, 37, 36, 26
};

// special thanks to the Chess Programming Wiki for this algorithm
int bitscan_forward(U64 bb)
{
	// folded MUST be an unsigned int (32bit), not U64 or
	// a normal int anything
	unsigned int folded;
	bb ^= bb-1;
	folded = (int) bb ^ (bb >> 32);
	return lsb_64_table[folded * 0x78291ACF >> 26];
}

U64 lsb(U64 bb)
{
	return bb & -bb;
}

// piece        the bitboard in bb->pieces[]
// dest         single bit set on the destination  square
struct Move *gen_move_from_1b(struct Bitboards *bb, struct Move *move_gen,
                              U64 piece, U64 dest)
{
	U64 piece_lsb;
	int piece_lsb_index;
	int dest_lsb_index;

	piece_lsb = lsb(piece);
	piece_lsb_index = bitscan_forward(piece_lsb);
	dest_lsb_index = bitscan_forward(dest);

	move_gen->start = piece_lsb_index;
	move_gen->end = dest_lsb_index;
	parse_move_for_mate(bb, move_gen);

	return move_gen;
}

bool king_has_moves(struct Bitboards *bb, struct Bitboards *copy,
                    struct Move *move_gen, enum Color turn)
{
	enum Piece color_king;
	U64 king;
	U64 attacks;
	U64 attacks_lsb;

	if (turn == WHITE)
		color_king = WHITE_KING;
	else
		color_king = BLACK_KING;

	king = bb->pieces[color_king];
	attacks = bb->attacks[color_king];
	while (attacks != 0) {
		attacks_lsb = lsb(attacks);
		gen_move_from_1b(bb, move_gen, king, attacks_lsb);
		if (validate_move(bb, copy, move_gen, turn))
			return true;
		else
			attacks ^= attacks_lsb;
	}
	return false;
}

// checker      piece bitboard of the checking piece
bool can_cap_checker(struct Bitboards *bb, struct Bitboards *copy,
                     struct Move *move_gen, enum Color turn, U64 checker)
{
	enum Piece i;
	enum Piece limit;
	if (turn == WHITE) {
		// check your own attacks
		i = WHITE_PAWNS;
		limit = TOTAL_ATTACKS;
	} else {
		i = BLACK_PAWNS;
		limit = WHITE_PAWNS;
	}

	U64 intersect;
	U64 piece;
	for (; i < limit; i++) {
		if (i == WHITE_KING || i == BLACK_KING)
			continue;

		piece = bb->pieces[i];
		intersect = bb->attacks[i] & checker;
		if (intersect) {
			gen_move_from_1b(bb, move_gen, piece, intersect);
			if (validate_move(bb, copy, move_gen, turn))
				return true;
		}
	}
	return false;
}

/*
bool checkmate(struct Bitboards *bb, struct Move *move)
{

king_has_moves():
  generate king moves
  for every king move
    if legal
      return true
  return false

HIGH-LEVEL ALGORITHM
if double check:
  return king_has_moves()
else:
  check for pieces' attacks
  if checking piece is attacked
    for any captures:
      if legal
        return false
  if king_has_moves()
    return false
  if distance check:
    for every interposition
      if legal
        return false
  return true



// king cannot have any legal moves
// there cannot be any legal interpositions
// no piece can capture the checking piece

if move->piece is not knight
  calculate rays until encounter enemy king
  that's our check_ray

  for each other piece
    if attacks[piece] & check_ray
      encode into a move
      the starting piece must be brute forced
      if move is legal, do move on bb->copy
        if king not in check
          return false

return true
}
*/