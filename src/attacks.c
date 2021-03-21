#include "attacks.h"
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

enum Ray
{
	RAY_NORTHWEST,
	RAY_NORTHEAST,
	RAY_SOUTHWEST,
	RAY_SOUTHEAST,
	RAY_NORTH,
	RAY_EAST,
	RAY_SOUTH,
	RAY_WEST
};

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

/*
calcualte a sliding piece attack, in ONE direction/ray

algorithm summary:
	enemy = enemy pieces' locations
	mask = empty squares and enemy pieces (places which we can attack!)
	piece = bitboard with the piece's or pieces' location(s)
	direction = well, the direction. one of the 9 one-step shifts

	START: load piece into shift
	the maximum number of one-step shifts is 7 (ie you are in the corner)
	for i in range(7)
		what value is direction?
			do corresponding one-step bitshift on shift

		save the shifted bit(s) into shift

		do logical AND between shift and mask, that determines if
		the newly shifted bit is an actual attack. ALSO LOAD THE
		NEW VALUE OF MASKED shift INTO shift

		if shift & mask equals 0, then this ray is now blocked.
			return;
		else, do logical OR between the newly shifted bit and attack

	return attack
*/
static U64 calc_ray(U64 enemy, U64 mask, U64 piece, enum Ray direction)
{
	// holds bitboard of ONE ray
	U64 result = 0;

	// the next bit in the sliding piece's attack scope
	U64 shift = piece;

	U64 save = shift;
	// previously, I would stop calculation if we shifted onto an
	// enemy piece. attack bitboards will be set on empty squares and
	// enemy's pieces, so I would set the bit on the enemy piece and
	// stop the loop.

	// HOWEVER, if there were 2+ rays to calculate, and one ray stopped
	// because it encountered an enemy piece, the other ray was also
	// forced to stop prematurely. therefore I keep an extra U64 save
	// If I have to stop one ray, I mask off that ray's bits from the
	// shifted bits, and load that back into shift.

	do
	{
		switch (direction)
		{
		case RAY_NORTHWEST:
			// use (=) instead of (|=)
			// ONLY save the shifted bit(s)
			shift = NORTHWEST(shift) & mask;
			break;

/* Mask off after EVERY shift!!!

consider this position: 5rk1/1p2pp1p/p2p2pB/1Kb5/8/5P2/q1r1QP1P/3R3R
there are two white rooks on h1 and d1. U64 piece and U64 shift would be 0x88

let's assume we are doing BITSHIFT(shift) without the mask
FIRST ITERATION:
	after one NORTH shift, shift = 0x8800
	since there's a white pawn on h2, that bit is masked off. shift & mask = 0x0800
	thus result shifts the d1 rook up 1 bit. result = 0x0800
SECOND ITERATION:
	we have to NORTH shift the variable "shift"!!!
	HOWEVER, it still saved the bad bit because we didn't mask it off!
	shift is still 0x8800, after another NORTH it equals 0x880000

	now h3 is set, and since it's an empty square, it's NOT masked off
	when loaded into result

if we DO mask off the bad bits, then the next iteration will set the bad bit
BUT this time it will mask it off. bad bits never get an opportunity to make
it past, and since every shift is by one square, we NEVER risk overshooting
the attack ray.
*/

		case RAY_NORTHEAST:
			shift = NORTHEAST(shift) & mask;
			break;
		case RAY_SOUTHWEST:
			shift = SOUTHWEST(shift) & mask;
			break;
		case RAY_SOUTHEAST:
			shift = SOUTHEAST(shift) & mask;
			break;
		case RAY_NORTH:
			shift = NORTH(shift) & mask;
			break;
		case RAY_EAST:
			shift = EAST(shift) & mask;
			break;
		case RAY_SOUTH:
			shift = SOUTH(shift) & mask;
			break;
		case RAY_WEST:
			shift = WEST(shift) & mask;
			break;
		}
		result |= shift;

		// we might have set a bit on attacked and non-empty square
		// if so, we must not go further, BUT on that ONE ray ONLY!
		// we can stop the bit from shifting further by masking it off
		// also prevents one ray from prematurely stopping a 2nd ray
		if (shift & enemy)
		{
			save = shift;

			// mask off the attacked bit ONLY
			save &= ~(shift & enemy);

			shift = save;
			// if shift becomes 0, then there are no more rays to
			// calculate and the loop ends.
		}
	} while (shift != 0);
	return result;
}

U64 bishop_attack(U64 piece, U64 self, U64 enemy)
{
	// mask = empty squares and enemy pieces
	U64 mask = ~(enemy | self) | enemy;
	U64 attack = 0;

	attack |= calc_ray(enemy, mask, piece, RAY_NORTHEAST);
	attack |= calc_ray(enemy, mask, piece, RAY_NORTHWEST);
	attack |= calc_ray(enemy, mask, piece, RAY_SOUTHEAST);
	attack |= calc_ray(enemy, mask, piece, RAY_SOUTHWEST);
	return attack;
}

U64 rook_attack(U64 piece, U64 self, U64 enemy)
{
	U64 mask = ~(enemy | self) | enemy;
	U64 attack = 0;

	attack |= calc_ray(enemy, mask, piece, RAY_NORTH);
	attack |= calc_ray(enemy, mask, piece, RAY_EAST);
	attack |= calc_ray(enemy, mask, piece, RAY_SOUTH);
	attack |= calc_ray(enemy, mask, piece, RAY_WEST);
	return attack;
}

// U64 queen_attack(U64 piece, U64 self, U64 enemy)
// {
// 	// combine the rook and bishop attack
// 	U64 attack = 0;
// 	attack |= bishop_attack(piece, self, enemy);
// 	attack |= rook_attack(piece, self, enemy);
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
	// these variables are just to make the lines shorter
	U64 piece, blacks, whites;
	for (int i = 0; i < TOTAL_ATTACKS; i++)
	{
		piece = bb->pieces[i];
		blacks = bb->black_all;
		whites = bb->white_all;
		switch (i)
		{
		case BLACK_PAWNS:
			bb->attacks[i] = pawn_attack(piece, blacks, BLACK);
			break;

		case WHITE_PAWNS:
			bb->attacks[i] = pawn_attack(piece, whites, WHITE);
			break;

		case BLACK_KNIGHTS:
			bb->attacks[i] = knight_attack(piece, blacks);
			break;

		case WHITE_KNIGHTS:
			bb->attacks[i] = knight_attack(piece, whites);
			break;

		case BLACK_BISHOPS:
			bb->attacks[i] = bishop_attack(piece, blacks, whites);
			break;

		case WHITE_BISHOPS:
			bb->attacks[i] = bishop_attack(piece, whites, blacks);
			break;

		case BLACK_ROOKS:
			bb->attacks[i] = rook_attack(piece, blacks, whites);
			break;

		case WHITE_ROOKS:
			bb->attacks[i] = rook_attack(piece, whites, blacks);
			break;

		case BLACK_QUEENS:
			// bb->attacks[i] = queen_attack(piece, blacks, whites);
			break;

		case WHITE_QUEENS:
			// bb->attacks[i] = queen_attack(piece, whites, blacks);
			break;

		case BLACK_KING:
			bb->attacks[i] = king_attack(piece, blacks);
			break;

		case WHITE_KING:
			bb->attacks[i] = king_attack(piece, whites);
			break;
		}
	}
	// pawn attacks and pawn pushes are separate
	U64 all = bb->white_all | bb->black_all;
	bb->w_pawn_pushes = pawn_push(bb->pieces[WHITE_PAWNS], all, WHITE);
	bb->b_pawn_pushes = pawn_push(bb->pieces[BLACK_PAWNS], all, BLACK);
}
