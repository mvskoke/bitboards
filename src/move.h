#ifndef MOVE_H
#define MOVE_H

void update_board(struct Bitboards *bb, char* move);
bool validate_move(struct Bitboards *bb, char *move, int turn);

#endif