#include "attacks.h"
#include "bitboards.h"
#include "colors.h"

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
			// code
			break;
		case BLACK_KNIGHTS:
		case WHITE_KNIGHTS:
			bb->attacks[i] = knight_attack(bb->pieces[i]);
			break;
		case BLACK_BISHOPS:
		case WHITE_BISHOPS:
			// code
			break;
		case BLACK_ROOKS:
		case WHITE_ROOKS:
			// code
			break;
		case BLACK_QUEENS:
		case WHITE_QUEENS:
			// code
			break;
		case BLACK_KING:
		case WHITE_KING:
			// code
			break;
		}
	}
	//update_pawn_pushes(WHITE);
	//update_pawn_pushes(BLACK);
}

U64 knight_attack(U64 bb)
{
	U64 tmp = bb;
	bb |= (tmp << 17) & NOT_A_FILE;
	bb |= (tmp << 15) & NOT_H_FILE;
	bb |= (tmp << 10) & NOT_AB_FILE;
	bb |= (tmp << 6) & NOT_HG_FILE;

	bb |= (tmp >> 6) & NOT_AB_FILE;
	bb |= (tmp >> 10) & NOT_HG_FILE;
	bb |= (tmp >> 15) & NOT_A_FILE;
	bb |= (tmp >> 17) & NOT_H_FILE;

	return bb;
}
