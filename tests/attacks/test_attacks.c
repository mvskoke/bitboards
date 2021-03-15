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
	init_bb(bb);

	TEST_ASSERT_EQUAL(0x0000000000A51842, knight_attack(bb->pieces[WHITE_KNIGHTS]));
	TEST_ASSERT_EQUAL(0x0028441044280000, knight_attack(0x0000001000000000));

	free(bb);
}

int main(void)
{
	UNITY_BEGIN();

	// RUN_TEST(test_update_attacks);
	RUN_TEST(test_knight_attack);

	return UNITY_END();
}