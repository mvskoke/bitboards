#include "bitboards.h"
#include "colors.h"

// bit masks
#define NOT_A_FILE  0xFEFEFEFEFEFEFEFE
#define NOT_AB_FILE 0xFCFCFCFCFCFCFCFC
#define NOT_H_FILE  0x7F7F7F7F7F7F7F7F
#define NOT_HG_FILE 0x3F3F3F3F3F3F3F3F

/************** TO DO **************/
// U64 pawn_attack(U64 piece)
// {
// 	U64 attack = 0;
// 	return attack;
// }

// U64 pawn_push(U64 pawns)
// {
// 	U64 attack = 0;
// 	return attack;
// }

// U64 bishop_attack(U64 piece)
// {
// 	U64 attack = 0;
// 	return attack;
// }

// U64 rook_attack(U64 piece)
// {
// 	U64 attack = 0;
// 	return attack;
// }

// U64 queen_attack(U64 piece)
// {
// 	U64 attack = 0;
// 	return attack;
// }

U64 knight_attack(U64 piece)
{
	U64 attack = 0;
	attack |= (piece << 17) & NOT_A_FILE;
	attack |= (piece << 15) & NOT_H_FILE;
	attack |= (piece << 10) & NOT_AB_FILE;
	attack |= (piece << 6) & NOT_HG_FILE;

	attack |= (piece >> 6) & NOT_AB_FILE;
	attack |= (piece >> 10) & NOT_HG_FILE;
	attack |= (piece >> 15) & NOT_A_FILE;
	attack |= (piece >> 17) & NOT_H_FILE;

	// remove the piece from its own attack bitboard
	attack &= ~piece;
	// ~piece will set every bit EXCEPT the piece locations
	// so AND'ing that with attack will remove the piece's
	// location from the attacks
	return attack;
}

U64 king_attack(U64 piece)
{
	U64 attack = 0;
	attack |= (piece << 7) & NOT_H_FILE;
	attack |=  piece << 8;
	attack |= (piece << 9) & NOT_A_FILE;

	attack |= (piece >> 1) & NOT_H_FILE;
	attack |= (piece << 1) & NOT_A_FILE;

	attack |= (piece >> 9) & NOT_H_FILE;
	attack |=  piece >> 8;
	attack |= (piece >> 7) & NOT_A_FILE;

	attack &= ~piece;
	return attack;
}

// if a move was made, make sure you update_board() BEFORE
// you update_attacks() because update_attacks() needs
// up-to-date info on piece locations
void update_attacks(struct Bitboards *bb)
{
	for (int i = 0; i < TOTAL_ATTACKS; i++)
	{
		// zero out the old attacks
		// bb->attacks[i] = 0;
		switch (i)
		{
		case BLACK_PAWNS:
		case WHITE_PAWNS:
			// bb->attacks[i] = pawn_attack(bb->pieces[i]);
			break;
		case BLACK_KNIGHTS:
		case WHITE_KNIGHTS:
			bb->attacks[i] = knight_attack(bb->pieces[i]);
			break;
		case BLACK_BISHOPS:
		case WHITE_BISHOPS:
			// bb->attacks[i] = bishop_attack(bb->pieces[i]);
			break;
		case BLACK_ROOKS:
		case WHITE_ROOKS:
			// bb->attacks[i] = rook_attack(bb->pieces[i]);
			break;
		case BLACK_QUEENS:
		case WHITE_QUEENS:
			// bb->attacks[i] = queen_attack(bb->pieces[i]);
			break;
		case BLACK_KING:
		case WHITE_KING:
			bb->attacks[i] = king_attack(bb->pieces[i]);
			break;
		}
	}
	// pawn attacks and pawn pushes are separate
	//pawn_push(bb->pieces[WHITE_PAWNS]);
	//pawn_push(bb->pieces[BLACK_PAWNS]);
}
