/** test_gameops.c

Test suite for all heavy duty game functions, such as move-making,
move parsing, handling data structures, and printing the board.

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/bitboards.h"
#include "../../src/colors.h"
#include "../../src/display.h"
#include "../../src/init.h"
#include "../../src/move.h"
#include "../../src/update.h"

#include "../../unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_parse_move(void)
{
	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);
	// I don't actually test prev here, I init it because
	// the init function needs it.

	// load the ruy lopez
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");

	// morphy defence
	TEST_ASSERT_EQUAL(curr, parse_move(bb, curr, "a7a6"));
	TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);
	TEST_ASSERT_EQUAL(A7, curr->start);
	TEST_ASSERT_EQUAL(A6, curr->end);
	TEST_ASSERT_EQUAL(BLACK_PAWNS, curr->piece);
	TEST_ASSERT_EQUAL(BLACK, curr->color);

	// berlin defence
	TEST_ASSERT_EQUAL(curr, parse_move(bb, curr, "g8f6"));
	TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);
	TEST_ASSERT_EQUAL(G8, curr->start);
	TEST_ASSERT_EQUAL(F6, curr->end);
	TEST_ASSERT_EQUAL(BLACK_KNIGHTS, curr->piece);
	TEST_ASSERT_EQUAL(BLACK, curr->color);

	// nothing
	TEST_ASSERT_EQUAL(NULL, parse_move(bb, curr, "a3a4"));
	TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);
	TEST_ASSERT_EQUAL(NULL, parse_move(bb, curr, "c5d6"));
	TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);

	TEST_ASSERT_EQUAL(curr, parse_move(bb, curr, "d7d6"));
	TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);
	TEST_ASSERT_EQUAL(D7, curr->start);
	TEST_ASSERT_EQUAL(D6, curr->end);
	TEST_ASSERT_EQUAL(BLACK_PAWNS, curr->piece);
	TEST_ASSERT_EQUAL(BLACK, curr->color);

	// promotion (an illegal one, but I have to test it)
	TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);
	TEST_ASSERT_EQUAL(curr, parse_move(bb, curr, "d7d8q"));
	TEST_ASSERT_EQUAL(BLACK_QUEENS, curr->promotion);
	TEST_ASSERT_EQUAL(D7, curr->start);
	TEST_ASSERT_EQUAL(D8, curr->end);
	TEST_ASSERT_EQUAL(BLACK_PAWNS, curr->piece);
	TEST_ASSERT_EQUAL(BLACK, curr->color);

	TEST_ASSERT_EQUAL(curr, parse_move(bb, curr, "f8c5"));
	TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);
	TEST_ASSERT_EQUAL(F8, curr->start);
	TEST_ASSERT_EQUAL(C5, curr->end);
	TEST_ASSERT_EQUAL(BLACK_BISHOPS, curr->piece);
	TEST_ASSERT_EQUAL(BLACK, curr->color);

	TEST_ASSERT_EQUAL(curr, parse_move(bb, curr, "e1e2"));
	TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);
	TEST_ASSERT_EQUAL(E1, curr->start);
	TEST_ASSERT_EQUAL(E2, curr->end);
	TEST_ASSERT_EQUAL(WHITE_KING, curr->piece);
	TEST_ASSERT_EQUAL(WHITE, curr->color);

	free(curr);
	free(prev);
	free(bb);
}

void test_update_board(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	// setting up the ruy lopez
	// 0xFDEF04121020EF9F
	if (parse_move(bb, curr, "e2e4")) {
		update_board(bb, curr);
		display_move(curr);
	}

	if (parse_move(bb, curr, "e7e5")) {
		update_board(bb, curr);
		display_move(curr);
	}

	// non-existent piece
	if (parse_move(bb, curr, "c5d5")) {
		update_board(bb, curr);
		display_move(curr);
	}
	// no move validation yet, don't try parsing other illegal
	// moves where the piece DOES exist, because parse_move()
	// only verifies the piece's existence!!!
	//validate_move() will be tested SEPARATELY.

	if (parse_move(bb, curr, "g1f3")) {
		update_board(bb, curr);
		display_move(curr);
	}

	if (parse_move(bb, curr, "b8c6")) {
		update_board(bb, curr);
		display_move(curr);
	}

	if (parse_move(bb, curr, "f1b5")) {
		update_board(bb, curr);
		display_move(curr);
	}

	// print_bb(bb->white_all | bb->black_all);
	bool ascii = true;
	print_bb_pretty(bb, BLACK, BLACK, ascii);
	print_bb_pretty(bb, WHITE, BLACK, ascii);

	ascii = false;
	print_bb_pretty(bb, BLACK, BLACK, ascii);
	print_bb_pretty(bb, WHITE, BLACK, ascii);

	print_bb_small(bb, BLACK);
	print_bb_small(bb, WHITE);

	TEST_ASSERT_EQUAL(0x1000EF00, bb->pieces[WHITE_PAWNS]);
	TEST_ASSERT_EQUAL(0xFDEF04121020EF9F, bb->white_all | bb->black_all);

	free(bb);
	free(curr);
	free(prev);
}

static void do_move(struct Move *curr, struct Move *prev, char command[], struct Bitboards *bb)
{
	printf("before transfer\n");
	display_move(curr);
	display_move(prev);
	transfer_move(curr, prev);

	printf("after transfer\n");
	display_move(curr);
	display_move(prev);

	if (parse_move(bb, curr, command)) {
		update_board(bb, curr);
	}

	printf("after parsing/moving\n");
	display_move(curr);
	display_move(prev);
	print_bb_small(bb, BLACK);
}

void test_transfer_move(void)
{
	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	char command[] = "e2e4";
	do_move(curr, prev, command, bb);
	strcpy(command, "e7e5");
	do_move(curr, prev, command, bb);

	printf("***end of test***\ncurr: ");
	display_move(curr);  // should be e7e5
	printf("prev: ");
	display_move(prev);  // should be e2e4

	free(bb);
	free(curr);
	free(prev);
}

void test_transfer_bitboards(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);
	struct Bitboards *copy = malloc(sizeof(struct Bitboards));
	init_bb(copy);
	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	/* INITIAL STAGE -- BOTH BITBOARDS ARE IDENTICAL */
	TEST_ASSERT_EQUAL_UINT64_ARRAY(bb->pieces, copy->pieces, TOTAL_BB);
	TEST_ASSERT_EQUAL_UINT64_ARRAY(bb->attacks, copy->attacks, TOTAL_ATTACKS);
	TEST_ASSERT_EQUAL(bb->white_all, copy->white_all);
	TEST_ASSERT_EQUAL(bb->black_all, copy->black_all);
	TEST_ASSERT_EQUAL(bb->w_pawn_pushes, copy->w_pawn_pushes);
	TEST_ASSERT_EQUAL(bb->b_pawn_pushes, copy->b_pawn_pushes);

	if (parse_move(bb, curr, "e2e4"))
		update_board(bb, curr);

	/* AFTER MOVE -- ONLY pieces[WHITE_PAWNS] HAS CHANGED */
	for (int i = 0; i < TOTAL_BB; i++)
	{
		// after e2e4, only WHITE_PAWNS
		if (i == WHITE_PAWNS)
			TEST_ASSERT_NOT_EQUAL(bb->pieces[i], copy->pieces[i]);
		else
			TEST_ASSERT_EQUAL(bb->pieces[i], copy->pieces[i]);
	}
	for (int j = 0; j < TOTAL_ATTACKS; j++)
	{
		// don't skip WHITE_PAWNS attacks, because I haven't
		// implemented attack calculation yet.
		TEST_ASSERT_EQUAL(bb->attacks[j], copy->attacks[j]);
	}
	TEST_ASSERT_NOT_EQUAL(bb->white_all, copy->white_all);
	TEST_ASSERT_EQUAL(bb->black_all, copy->black_all);

	// not really a need to check w_pawn_pushes bitboards in this
	// stage of this test. we'll need to update_attacks() to check,
	// which we will test in another module
	// TEST_ASSERT_NOT_EQUAL(bb->w_pawn_pushes, copy->w_pawn_pushes);
	TEST_ASSERT_EQUAL(bb->b_pawn_pushes, copy->b_pawn_pushes);

	transfer_bb(bb, copy);

	/* AFTER TRANSFER -- BOTH BITBOARDS SHOULD BE IDENTICAL AGAIN */
	TEST_ASSERT_EQUAL_UINT64_ARRAY(bb->pieces, copy->pieces, TOTAL_BB);
	TEST_ASSERT_EQUAL_UINT64_ARRAY(bb->attacks, copy->attacks, TOTAL_ATTACKS);
	TEST_ASSERT_EQUAL(bb->white_all, copy->white_all);
	TEST_ASSERT_EQUAL(bb->black_all, copy->black_all);

	free(bb);
	free(copy);
	free(curr);
	free(prev);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_parse_move);
	RUN_TEST(test_update_board);
	RUN_TEST(test_transfer_move);
	RUN_TEST(test_transfer_bitboards);

	return UNITY_END();
}