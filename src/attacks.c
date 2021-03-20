#include "bitboards.h"
#include "colors.h"

// bit masks
#define SECOND_RANK  0x000000000000FF00
#define THIRD_RANK   0x0000000000FF0000
#define SIXTH_RANK   0x0000FF0000000000
#define SEVENTH_RANK 0x00FF000000000000

#define NOT_A_FILE   0xFEFEFEFEFEFEFEFE
#define NOT_AB_FILE  0xFCFCFCFCFCFCFCFC
#define NOT_H_FILE   0x7F7F7F7F7F7F7F7F
#define NOT_HG_FILE  0x3F3F3F3F3F3F3F3F

// one-step bit shift with bitmask
#define NORTHWEST(bb) ((bb << 7) & NOT_H_FILE)
#define NORTH(bb)      (bb << 8)
#define NORTHEAST(bb) ((bb << 9) & NOT_A_FILE)

#define EAST(bb)      ((bb << 1) & NOT_A_FILE)
#define WEST(bb)      ((bb >> 1) & NOT_H_FILE)

#define SOUTHWEST(bb) ((bb >> 9) & NOT_H_FILE)
#define SOUTH(bb)      (bb >> 8)
#define SOUTHEAST(bb) ((bb >> 7) & NOT_A_FILE)

// squares attacked by pawn(s) (diagonal captures)
// exclude your own pieces
// U64 all = all pieces of enum Color color
U64 pawn_attack(U64 piece, U64 all, enum Color color)
{
	U64 attack = 0;
	if (color == WHITE)
	{
		attack |= NORTHEAST(piece);
		attack |= NORTHWEST(piece);
	}
	else
	{
		attack |= SOUTHWEST(piece);
		attack |= SOUTHEAST(piece);
	}

	attack &= ~all;
	return attack;
}

// squares to which a pawn(s) can push itself
// exclude your pieces AND enemies' pieces because these aren't captures
// U64 all = ALL pieces on the board
U64 pawn_push(U64 pawns, U64 all, enum Color color)
{
	U64 push = 0;

	// find pieces on third/sixth rank which block pawns
	U64 white_blocked = (all & THIRD_RANK) >> 8;
	U64 black_blocked = (all & SIXTH_RANK) << 8;

	// find UNBLOCKED pawns on the starting rank
	U64 white_twice = pawns & SECOND_RANK & ~white_blocked;
	U64 black_twice = pawns & SEVENTH_RANK & ~black_blocked;

	if (color == WHITE)
	{
		// up twice if on the starting rank
		push |= NORTH(NORTH(white_twice));
		push |= NORTH(pawns);
	}
	else
	{
		push |= SOUTH(SOUTH(black_twice));
		push |= SOUTH(pawns);
	}

	push &= ~all;
	return push;
}

// squares to which a knight(s) can jump
// exclude your own pieces
// U64 all = all pieces of knights' same color
U64 knight_attack(U64 piece, U64 all)
{
	U64 attack = 0;
	attack |= (piece << 17) & NOT_A_FILE;
	attack |= (piece << 15) & NOT_H_FILE;
	attack |= (piece << 10) & NOT_AB_FILE;
	attack |= (piece << 6)  & NOT_HG_FILE;

	attack |= (piece >> 6)  & NOT_AB_FILE;
	attack |= (piece >> 10) & NOT_HG_FILE;
	attack |= (piece >> 15) & NOT_A_FILE;
	attack |= (piece >> 17) & NOT_H_FILE;

	attack &= ~all;
	return attack;
}

// U64 bishop_attack(U64 piece, U64 all)
// {
// 	U64 attack = 0;
// 	return attack;
// }

// U64 rook_attack(U64 piece, U64 all)
// {
// 	U64 attack = 0;
// 	return attack;
// }

// U64 queen_attack(U64 piece, U64 all)
// {
// 	U64 attack = 0;
// 	return attack;
// }

// squares to which a king(s) can jump
// exclude your own pieces
// U64 all = all pieces of king's same color
U64 king_attack(U64 piece, U64 all)
{
	U64 attack = 0;
	attack |= NORTHWEST(piece);
	attack |= NORTH(piece);
	attack |= NORTHEAST(piece);

	attack |= WEST(piece);
	attack |= EAST(piece);

	attack |= SOUTHWEST(piece);
	attack |= SOUTH(piece);
	attack |= SOUTHEAST(piece);

	attack &= ~all;
	return attack;
}

// if a move was made, make sure you update_board() BEFORE
// you update_attacks() because update_attacks() needs
// up-to-date info on piece locations
void update_attacks(struct Bitboards *bb)
{
	U64 piece;
	for (int i = 0; i < TOTAL_ATTACKS; i++)
	{
		// make the line length shorter
		piece = bb->pieces[i];
		switch (i)
		{
		case BLACK_PAWNS:
			bb->attacks[i] = pawn_attack(piece, bb->black_all, BLACK);
			break;

		case WHITE_PAWNS:
			bb->attacks[i] = pawn_attack(piece, bb->white_all, WHITE);
			break;

		case BLACK_KNIGHTS:
			bb->attacks[i] = knight_attack(piece, bb->black_all);
			break;

		case WHITE_KNIGHTS:
			bb->attacks[i] = knight_attack(piece, bb->white_all);
			break;

		case BLACK_BISHOPS:
			// bb->attacks[i] = bishop_attack(piece, bb->black_all);
			break;

		case WHITE_BISHOPS:
			// bb->attacks[i] = bishop_attack(piece, bb->white_all);
			break;

		case BLACK_ROOKS:
			// bb->attacks[i] = rook_attack(piece, bb->black_all);
			break;

		case WHITE_ROOKS:
			// bb->attacks[i] = rook_attack(piece, bb->white_all);
			break;

		case BLACK_QUEENS:
			// bb->attacks[i] = queen_attack(piece, bb->black_all);
			break;

		case WHITE_QUEENS:
			// bb->attacks[i] = queen_attack(piece, bb->white_all);
			break;

		case BLACK_KING:
			bb->attacks[i] = king_attack(piece, bb->black_all);
			break;

		case WHITE_KING:
			bb->attacks[i] = king_attack(piece, bb->white_all);
			break;
		}
	}
	// pawn attacks and pawn pushes are separate
	U64 all = bb->white_all | bb->black_all;
	bb->w_pawn_pushes = pawn_push(bb->pieces[WHITE_PAWNS], all, WHITE);
	bb->b_pawn_pushes = pawn_push(bb->pieces[BLACK_PAWNS], all, BLACK);
}
