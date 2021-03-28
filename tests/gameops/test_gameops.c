/** test_gameops.c

Test suite for all heavy duty game functions, such as move-making,
move parsing, handling data structures, and printing the board.

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -I../../src/
#include "bitboards.h"
#include "colors.h"
#include "display.h"
#include "init.h"
#include "move.h"
#include "update.h"

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

	// no move validation yet, don't try parsing other illegal
	// moves where the piece DOES exist, because parse_move()
	// only verifies the piece's existence!!!
	//validate_move() will be tested SEPARATELY.

	// setting up the ruy lopez
	// 0xFDEF04121020EF9F
	if (parse_move(bb, curr, "e2e4"))
	{
		update_board(bb, curr);
		TEST_ASSERT_EQUAL(E2, curr->start);
		TEST_ASSERT_EQUAL(E4, curr->end);
		TEST_ASSERT_EQUAL(WHITE, curr->color);
		TEST_ASSERT_EQUAL(WHITE_PAWNS, curr->piece);
	}

	if (parse_move(bb, curr, "e7e5"))
	{
		update_board(bb, curr);
		TEST_ASSERT_EQUAL(E7, curr->start);
		TEST_ASSERT_EQUAL(E5, curr->end);
		TEST_ASSERT_EQUAL(BLACK, curr->color);
		TEST_ASSERT_EQUAL(BLACK_PAWNS, curr->piece);
	}

	if (parse_move(bb, curr, "g1f3"))
	{
		update_board(bb, curr);
		TEST_ASSERT_EQUAL(G1, curr->start);
		TEST_ASSERT_EQUAL(F3, curr->end);
		TEST_ASSERT_EQUAL(WHITE, curr->color);
		TEST_ASSERT_EQUAL(WHITE_KNIGHTS, curr->piece);
	}

	if (parse_move(bb, curr, "b8c6"))
	{
		update_board(bb, curr);
		TEST_ASSERT_EQUAL(B8, curr->start);
		TEST_ASSERT_EQUAL(C6, curr->end);
		TEST_ASSERT_EQUAL(BLACK, curr->color);
		TEST_ASSERT_EQUAL(BLACK_KNIGHTS, curr->piece);
	}

	if (parse_move(bb, curr, "f1b5"))
	{
		update_board(bb, curr);
		TEST_ASSERT_EQUAL(F1, curr->start);
		TEST_ASSERT_EQUAL(B5, curr->end);
		TEST_ASSERT_EQUAL(WHITE, curr->color);
		TEST_ASSERT_EQUAL(WHITE_BISHOPS, curr->piece);
	}

	/* uncomment if you want to print the boards in all their forms */
	// bool ascii = true;
	// print_bb_pretty(bb, BLACK, BLACK, ascii);
	// print_bb_pretty(bb, WHITE, BLACK, ascii);

	// ascii = false;
	// print_bb_pretty(bb, BLACK, BLACK, ascii);
	// print_bb_pretty(bb, WHITE, BLACK, ascii);

	// print_bb_small(bb, BLACK);
	// print_bb_small(bb, WHITE);

	TEST_ASSERT_EQUAL(0x1000EF00, bb->pieces[WHITE_PAWNS]);
	TEST_ASSERT_EQUAL(0xFDEF04121020EF9F, bb->all);

	free(bb);
	free(curr);
	free(prev);
}

void test_transfer_move(void)
{
	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	/* test the initialized values*/
	TEST_ASSERT_EQUAL(BAD_SQUARE, curr->start);
	TEST_ASSERT_EQUAL(BAD_SQUARE, curr->end);
	TEST_ASSERT_EQUAL(WHITE, curr->color);
	TEST_ASSERT_EQUAL(NONEXISTENT, curr->piece);
	TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);

	TEST_ASSERT_EQUAL(BAD_SQUARE, prev->start);
	TEST_ASSERT_EQUAL(BAD_SQUARE, prev->end);
	TEST_ASSERT_EQUAL(WHITE, prev->color);
	TEST_ASSERT_EQUAL(NONEXISTENT, prev->piece);
	TEST_ASSERT_EQUAL(NONEXISTENT, prev->promotion);

	/* FIRST TRANSFER */
	transfer_move(curr, prev);

	// nothing should have changed
	TEST_ASSERT_EQUAL(curr->start, prev->start);
	TEST_ASSERT_EQUAL(curr->end, prev->end);
	TEST_ASSERT_EQUAL(curr->color, prev->color);
	TEST_ASSERT_EQUAL(curr->piece, prev->piece);
	TEST_ASSERT_EQUAL(curr->promotion, prev->promotion);

	// after parsing, curr will change
	if (parse_move(bb, curr, "e2e4"))
	{
		update_board(bb, curr);
		TEST_ASSERT_EQUAL(E2, curr->start);
		TEST_ASSERT_EQUAL(E4, curr->end);
		TEST_ASSERT_EQUAL(WHITE, curr->color);
		TEST_ASSERT_EQUAL(WHITE_PAWNS, curr->piece);
		TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);

		// prev should not have changed
		TEST_ASSERT_EQUAL(BAD_SQUARE, prev->start);
		TEST_ASSERT_EQUAL(BAD_SQUARE, prev->end);
		TEST_ASSERT_EQUAL(WHITE, prev->color);
		TEST_ASSERT_EQUAL(NONEXISTENT, prev->piece);
		TEST_ASSERT_EQUAL(NONEXISTENT, prev->promotion);
	}

	/* SECOND TRANSFER */
	transfer_move(curr, prev);

	// prev will contain move information for "e2e4"
	TEST_ASSERT_EQUAL(E2, prev->start);
	TEST_ASSERT_EQUAL(E4, prev->end);
	TEST_ASSERT_EQUAL(WHITE, prev->color);
	TEST_ASSERT_EQUAL(WHITE_PAWNS, prev->piece);
	TEST_ASSERT_EQUAL(NONEXISTENT, prev->promotion);

	if (parse_move(bb, curr, "e7e5"))
	{
		update_board(bb, curr);
		TEST_ASSERT_EQUAL(E7, curr->start);
		TEST_ASSERT_EQUAL(E5, curr->end);
		TEST_ASSERT_EQUAL(BLACK, curr->color);
		TEST_ASSERT_EQUAL(BLACK_PAWNS, curr->piece);
		TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);
	}

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