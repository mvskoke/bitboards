/** test_attacks.c

Test suite for attack calculation and move validation

*/

#include <stdio.h>
#include <stdlib.h>

#include "../../src/attacks.h"
#include "../../src/bitboards.h"
#include "../../src/colors.h"
#include "../../src/init.h"
#include "../../src/update.h"

#include "../../unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_update_attacks(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	// I don't need a *prev for this test
	struct Move *curr = malloc(sizeof(struct Move));
	if (curr == NULL)
	{
		fprintf(stderr, "ERROR: could not allocate enough memory\n");
		exit(EXIT_FAILURE);
	}

	if (parse_move(bb, curr, "e2e4"))
		update_board(bb, curr);

	// update_attacks(bb);

	// e2e4 moves the pawn, and opens up the king, queen, bishop,
	// and knight, so the only attacks which should be updated are
	// white's king, queen, f1 bishop, g1 knight, and pawns.
	// TEST_ASSERT_EQUAL(0x0000000000001010, bb->attacks[WHITE_KING]);
	// TEST_ASSERT_EQUAL(0x0000008040201000, bb->attacks[WHITE_QUEENS]);
	// TEST_ASSERT_EQUAL(0x0000010204081000, bb->attacks[WHITE_BISHOPS]);
	// TEST_ASSERT_EQUAL(0x0000000000A51000, bb->attacks[WHITE_KNIGHTS]);
	// TEST_ASSERT_EQUAL(0x0000002800FF0000, bb->attacks[WHITE_PAWNS]);

	// TEST_ASSERT_EQUAL(0x00000010EFEF0000, bb->wpawn_pushes);
	// TEST_ASSERT_EQUAL(0x0000FFFF00000000, bb->bpawn_pushes);

	// black pieces should remain unchanged
	// TEST_ASSERT_EQUAL(0x0000FF0000000000, bb->attacks[BLACK_PAWNS]);
	// TEST_ASSERT_EQUAL(0x0000A50000000000, bb->attacks[BLACK_KNIGHTS]);
	// TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_BISHOPS]);
	// TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_ROOKS]);
	// TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_QUEENS]);
	// TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_KING]);

	free(bb);
	free(curr);
}

void test_knight_attack(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	/* from FEN position */

	// white knight on e5
	TEST_ASSERT_EQUAL(0x0028440044280000, knight_attack(bb->pieces[WHITE_KNIGHTS]));
	// black knight on d5
	TEST_ASSERT_EQUAL(0x0014220022140000, knight_attack(bb->pieces[BLACK_KNIGHTS]));

	if (parse_move(bb, curr, "e5d7"))
		update_board(bb, curr);

	TEST_ASSERT_EQUAL(0x2200221400000000, knight_attack(bb->pieces[WHITE_KNIGHTS]));

	/* knight pairs */

	// starting squares
	TEST_ASSERT_EQUAL(0x0000000000A51800, knight_attack(0x0000000000000042));
	TEST_ASSERT_EQUAL(0x0018A50000000000, knight_attack(0x4200000000000000));
	// a5 b5
	TEST_ASSERT_EQUAL(0x0002040004020000 | 0x0005080008050000, knight_attack(0x0000000300000000));
	// e5 g1
	TEST_ASSERT_EQUAL(0x0028440044A81000, knight_attack(0x0000001000000040));

	/* lone knights */

	TEST_ASSERT_EQUAL(0x0028440044280000, knight_attack(0x0000001000000000));  //e5
	TEST_ASSERT_EQUAL(0x00000A1100110A00, knight_attack(0x0000000004000000));  //c4

	TEST_ASSERT_EQUAL(0x0002040004020000, knight_attack(0x0000000100000000));  //a5
	TEST_ASSERT_EQUAL(0x0005080008050000, knight_attack(0x0000000200000000));  //b5
	TEST_ASSERT_EQUAL(0x0204000402000000, knight_attack(0x0000010000000000));  //a6
	TEST_ASSERT_EQUAL(0x0508000805000000, knight_attack(0x0000020000000000));  //b6
	TEST_ASSERT_EQUAL(0x0800080500000000, knight_attack(0x0002000000000000));  //b7
	TEST_ASSERT_EQUAL(0x1100110A00000000, knight_attack(0x0004000000000000));  //c7
	TEST_ASSERT_EQUAL(0x0A1100110A000000, knight_attack(0x0000040000000000));  //c6

	TEST_ASSERT_EQUAL(0x0040200020400000, knight_attack(0x0000008000000000));  //h5
	TEST_ASSERT_EQUAL(0x00A0100010A00000, knight_attack(0x0000004000000000));  //g5
	TEST_ASSERT_EQUAL(0x4020002040000000, knight_attack(0x0000800000000000));  //h6
	TEST_ASSERT_EQUAL(0xA0100010A0000000, knight_attack(0x0000400000000000));  //g6
	TEST_ASSERT_EQUAL(0x100010A000000000, knight_attack(0x0040000000000000));  //g7
	TEST_ASSERT_EQUAL(0x8800885000000000, knight_attack(0x0020000000000000));  //f7
	TEST_ASSERT_EQUAL(0x5088008850000000, knight_attack(0x0000200000000000));  //f6

	TEST_ASSERT_EQUAL(0x0000000002040004, knight_attack(0x0000000000000100));  //a2
	TEST_ASSERT_EQUAL(0x0000000005080008, knight_attack(0x0000000000000200));  //b2
	TEST_ASSERT_EQUAL(0x0000000040200020, knight_attack(0x0000000000008000));  //h2
	TEST_ASSERT_EQUAL(0x00000000A0100010, knight_attack(0x0000000000004000));  //g2
	TEST_ASSERT_EQUAL(0x000000A0100010A0, knight_attack(0x0000000000400000));  //g3
	TEST_ASSERT_EQUAL(0x0000005088008850, knight_attack(0x0000000000200000));  //f3
	TEST_ASSERT_EQUAL(0x0000000050880088, knight_attack(0x0000000000002000));  //f2

	free(bb);
	free(curr);
	free(prev);
}

void test_king_attack(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb_fen(bb, "5rk1/1p2pp1p/p2p2pB/1Kb5/8/5P2/q1r1QP1P/3R3R");

	/* from FEN position */
	TEST_ASSERT_EQUAL(0x0000070507000000, king_attack(bb->pieces[WHITE_KING]));
	TEST_ASSERT_EQUAL(0xA0E0000000000000, king_attack(bb->pieces[BLACK_KING]));

	/* from hard-coded positions */
	TEST_ASSERT_EQUAL(0x0000030203000000, king_attack(0x0000000100000000));  //a5
	TEST_ASSERT_EQUAL(0x0000c040c0000000, king_attack(0x0000008000000000));  //h5
	TEST_ASSERT_EQUAL(0x0000000000000302, king_attack(0x0000000000000001));  //a1
	TEST_ASSERT_EQUAL(0x000000000000c040, king_attack(0x0000000000000080));  //h1
	TEST_ASSERT_EQUAL(0x0203000000000000, king_attack(0x0100000000000000));  //a8
	TEST_ASSERT_EQUAL(0x40c0000000000000, king_attack(0x8000000000000000));  //h8

	// starting positions
	TEST_ASSERT_EQUAL(0x0000000000003828, king_attack(0x0000000000000010));  // e1
	TEST_ASSERT_EQUAL(0x2838000000000000, king_attack(0x1000000000000000));  // e8

	free(bb);
}

/*********** TO DO ***********/

// void test_pawn_attack(void)
// {
// 	;
// }

// void test_bishop_attack(void)
// {
// 	;
// }

// void test_rook_attack(void)
// {
// 	;
// }

// void test_queen_attack(void)
// {
// 	;
// }

// void test_pawn_push(void)
// {
// 	;
// }

int main(void)
{
	UNITY_BEGIN();

	// RUN_TEST(test_update_attacks);
	RUN_TEST(test_knight_attack);
	RUN_TEST(test_king_attack);
	// RUN_TEST(test_pawn_attack);
	// RUN_TEST(test_bishop_attack);
	// RUN_TEST(test_rook_attack);
	// RUN_TEST(test_queen_attack);
	// RUN_TEST(test_pawn_push);

	return UNITY_END();
}