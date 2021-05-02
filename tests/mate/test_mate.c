/** test_mate.c

Test suite for all checkmate and mate detection functions.

*/

#include <stdlib.h>

// -I../../src/
#include "bitboards.h"
#include "init.h"
#include "mate.h"
#include "move.h"

#include "../../unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

// making sure the Chess Programming Wiki isn't lying to me
void test_bitscan_forward(void)
{
	TEST_ASSERT_EQUAL(0,  bitscan_forward(0x0000000000000001));
	TEST_ASSERT_EQUAL(1,  bitscan_forward(0x0000000000000002));
	TEST_ASSERT_EQUAL(2,  bitscan_forward(0x0000000000000004));
	TEST_ASSERT_EQUAL(3,  bitscan_forward(0x0000000000000008));
	TEST_ASSERT_EQUAL(4,  bitscan_forward(0x0000000000000010));
	TEST_ASSERT_EQUAL(5,  bitscan_forward(0x0000000000000020));
	TEST_ASSERT_EQUAL(6,  bitscan_forward(0x0000000000000040));
	TEST_ASSERT_EQUAL(7,  bitscan_forward(0x0000000000000080));
	TEST_ASSERT_EQUAL(8,  bitscan_forward(0x0000000000000100));
	TEST_ASSERT_EQUAL(9,  bitscan_forward(0x0000000000000200));
	TEST_ASSERT_EQUAL(10, bitscan_forward(0x0000000000000400));
	TEST_ASSERT_EQUAL(11, bitscan_forward(0x0000000000000800));
	TEST_ASSERT_EQUAL(12, bitscan_forward(0x0000000000001000));
	TEST_ASSERT_EQUAL(13, bitscan_forward(0x0000000000002000));
	TEST_ASSERT_EQUAL(14, bitscan_forward(0x0000000000004000));
	TEST_ASSERT_EQUAL(15, bitscan_forward(0x0000000000008000));
	TEST_ASSERT_EQUAL(16, bitscan_forward(0x0000000000010000));
	TEST_ASSERT_EQUAL(17, bitscan_forward(0x0000000000020000));
	TEST_ASSERT_EQUAL(18, bitscan_forward(0x0000000000040000));
	TEST_ASSERT_EQUAL(19, bitscan_forward(0x0000000000080000));
	TEST_ASSERT_EQUAL(20, bitscan_forward(0x0000000000100000));
	TEST_ASSERT_EQUAL(21, bitscan_forward(0x0000000000200000));
	TEST_ASSERT_EQUAL(22, bitscan_forward(0x0000000000400000));
	TEST_ASSERT_EQUAL(23, bitscan_forward(0x0000000000800000));
	TEST_ASSERT_EQUAL(24, bitscan_forward(0x0000000001000000));
	TEST_ASSERT_EQUAL(25, bitscan_forward(0x0000000002000000));
	TEST_ASSERT_EQUAL(26, bitscan_forward(0x0000000004000000));
	TEST_ASSERT_EQUAL(27, bitscan_forward(0x0000000008000000));
	TEST_ASSERT_EQUAL(28, bitscan_forward(0x0000000010000000));
	TEST_ASSERT_EQUAL(29, bitscan_forward(0x0000000020000000));
	TEST_ASSERT_EQUAL(30, bitscan_forward(0x0000000040000000));
	TEST_ASSERT_EQUAL(31, bitscan_forward(0x0000000080000000));
	TEST_ASSERT_EQUAL(32, bitscan_forward(0x0000000100000000));
	TEST_ASSERT_EQUAL(33, bitscan_forward(0x0000000200000000));
	TEST_ASSERT_EQUAL(34, bitscan_forward(0x0000000400000000));
	TEST_ASSERT_EQUAL(35, bitscan_forward(0x0000000800000000));
	TEST_ASSERT_EQUAL(36, bitscan_forward(0x0000001000000000));
	TEST_ASSERT_EQUAL(37, bitscan_forward(0x0000002000000000));
	TEST_ASSERT_EQUAL(38, bitscan_forward(0x0000004000000000));
	TEST_ASSERT_EQUAL(39, bitscan_forward(0x0000008000000000));
	TEST_ASSERT_EQUAL(40, bitscan_forward(0x0000010000000000));
	TEST_ASSERT_EQUAL(41, bitscan_forward(0x0000020000000000));
	TEST_ASSERT_EQUAL(42, bitscan_forward(0x0000040000000000));
	TEST_ASSERT_EQUAL(43, bitscan_forward(0x0000080000000000));
	TEST_ASSERT_EQUAL(44, bitscan_forward(0x0000100000000000));
	TEST_ASSERT_EQUAL(45, bitscan_forward(0x0000200000000000));
	TEST_ASSERT_EQUAL(46, bitscan_forward(0x0000400000000000));
	TEST_ASSERT_EQUAL(47, bitscan_forward(0x0000800000000000));
	TEST_ASSERT_EQUAL(48, bitscan_forward(0x0001000000000000));
	TEST_ASSERT_EQUAL(49, bitscan_forward(0x0002000000000000));
	TEST_ASSERT_EQUAL(50, bitscan_forward(0x0004000000000000));
	TEST_ASSERT_EQUAL(51, bitscan_forward(0x0008000000000000));
	TEST_ASSERT_EQUAL(52, bitscan_forward(0x0010000000000000));
	TEST_ASSERT_EQUAL(53, bitscan_forward(0x0020000000000000));
	TEST_ASSERT_EQUAL(54, bitscan_forward(0x0040000000000000));
	TEST_ASSERT_EQUAL(55, bitscan_forward(0x0080000000000000));
	TEST_ASSERT_EQUAL(56, bitscan_forward(0x0100000000000000));
	TEST_ASSERT_EQUAL(57, bitscan_forward(0x0200000000000000));
	TEST_ASSERT_EQUAL(58, bitscan_forward(0x0400000000000000));
	TEST_ASSERT_EQUAL(59, bitscan_forward(0x0800000000000000));
	TEST_ASSERT_EQUAL(60, bitscan_forward(0x1000000000000000));
	TEST_ASSERT_EQUAL(61, bitscan_forward(0x2000000000000000));
	TEST_ASSERT_EQUAL(62, bitscan_forward(0x4000000000000000));
	TEST_ASSERT_EQUAL(63, bitscan_forward(0x8000000000000000));

	TEST_ASSERT_EQUAL(3,  bitscan_forward(1234567898765432));
	TEST_ASSERT_EQUAL(18, bitscan_forward(8004398046511104));
	TEST_ASSERT_EQUAL(58, bitscan_forward(0x0400000000000000));
}

void test_gen_move_from_1b(void)
{
	U64 piece;
	U64 dest;

	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	// triple fork
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	struct Move *move_gen = malloc(sizeof(struct Move));

	piece = bb->pieces[BLACK_KING];
	dest = bb->attacks[BLACK_KING];

	TEST_ASSERT_EQUAL(C8, bitscan_forward(piece));
	TEST_ASSERT_EQUAL(D7, bitscan_forward(dest));

	gen_move_from_1b(bb, move_gen, piece, dest);

	TEST_ASSERT_EQUAL(BLACK, move_gen->color);
	TEST_ASSERT_EQUAL(BLACK_KING, move_gen->piece);
	TEST_ASSERT_EQUAL(OTHER, move_gen->type);
	TEST_ASSERT_EQUAL(NONEXISTENT, move_gen->captured);
	TEST_ASSERT_EQUAL(C8, move_gen->start);
	TEST_ASSERT_EQUAL(D7, move_gen->end);

	// cool mate
	init_bb_fen(bb, "5rk1/1p2pp1p/p2p2pB/1Kb5/8/5P2/q1r1QP1P/3R3R");

	piece = bb->pieces[WHITE_KING];
	dest = bb->attacks[WHITE_KING];

	TEST_ASSERT_EQUAL(B5, bitscan_forward(piece));
	TEST_ASSERT_EQUAL(A4, bitscan_forward(dest));

	gen_move_from_1b(bb, move_gen, piece, dest);

	TEST_ASSERT_EQUAL(WHITE, move_gen->color);
	TEST_ASSERT_EQUAL(WHITE_KING, move_gen->piece);
	TEST_ASSERT_EQUAL(OTHER, move_gen->type);
	TEST_ASSERT_EQUAL(NONEXISTENT, move_gen->captured);
	TEST_ASSERT_EQUAL(B5, move_gen->start);
	TEST_ASSERT_EQUAL(A4, move_gen->end);

	free(bb);
	free(move_gen);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_bitscan_forward);
	RUN_TEST(test_gen_move_from_1b);

	return UNITY_END();
}