/** test_validate.c

Test suite for testing move validation

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// -I../../src/
#include "attacks.h"
#include "bitboards.h"
#include "colors.h"
#include "init.h"
#include "move.h"
#include "update.h"
#include "validate.h"

#include "../../unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

// validate_pawn_move() is only called if the piece exists
// and the destination is pseudo-legal
void test_validate_pawn_move(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	update_attacks(bb);

	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	/* pawn pushes */
	parse_move(bb, curr, "a7a6");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "d7d6");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "d7d5");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));

	parse_move(bb, curr, "c7c6");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "c7c5");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	/* pawn captures */
	parse_move(bb, curr, "a7b6");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "c7b6");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "d7c6");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "e5f4");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "e5d4");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	free(bb);
	free(curr);
	free(prev);
}

/*
void test_validate_move(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	int turn = BLACK;

	free(bb);
}
*/
int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_validate_pawn_move);
	// RUN_TEST(test_validate_move);

	return UNITY_END();
}