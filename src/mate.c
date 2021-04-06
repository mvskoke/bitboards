#include "mate.h"

bool checkmate(struct Bitboards *bb, struct Move *move)
{
/*
// king cannot have any legal moves
// there cannot be any legal interpositions
// no piece can capture the checking piece

generate king moves
for each king move
  if validate_move(move)
    return false

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
*/
}
