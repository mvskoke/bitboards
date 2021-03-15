/** test_gameops.c

Test suite for all regular game functions, such as move-making,
move validation, and printing the board.

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/bitboards.h"
#include "../../src/colors.h"
#include "../../src/display.h"
#include "../../src/init.h"
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

	// it has the exact same implementation as curr anyway,
	// so its functionality will be tested when the main program
	// actually needs it.

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
	TEST_ASSERT_EQUAL(D7, curr->start);
	TEST_ASSERT_EQUAL(D8, curr->end);
	TEST_ASSERT_EQUAL(BLACK_PAWNS, curr->piece);
	TEST_ASSERT_EQUAL(BLACK, curr->color);
	TEST_ASSERT_EQUAL(BLACK_QUEENS, curr->promotion);

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
	// ADD CALL TO VALIDATION ONCE THAT'S IMPLEMENTED!!!
	if (parse_move(bb, curr, "c5d5")) {
		update_board(bb, curr);
		display_move(curr);
	}


	/********************************************************

	illegal move -- MUST VALIDATE AFTER PARSING!

	********************************************************/

	// if (parse_move(bb, curr, "e1f1")) {
	// 	update_board(bb, curr);
	// 	display_move(curr);
	// }

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

	// print_bb(bb->pieces[WHITE_ALL] | bb->pieces[BLACK_ALL]);
	bool ascii = true;
	print_bb_pretty(bb, BLACK, BLACK, ascii);
	print_bb_pretty(bb, WHITE, BLACK, ascii);

	ascii = false;
	print_bb_pretty(bb, BLACK, BLACK, ascii);
	print_bb_pretty(bb, WHITE, BLACK, ascii);

	print_bb_small(bb, BLACK);
	print_bb_small(bb, WHITE);

	TEST_ASSERT_EQUAL(0x1000EF00, bb->pieces[WHITE_PAWNS]);
	TEST_ASSERT_EQUAL(0xFDEF04121020EF9F, bb->pieces[WHITE_ALL] | bb->pieces[BLACK_ALL]);

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

	TEST_ASSERT_EQUAL_UINT64_ARRAY(bb->pieces, copy->pieces, TOTAL_BB);
	TEST_ASSERT_EQUAL_UINT64_ARRAY(bb->attacks, copy->attacks, TOTAL_ATTACKS);

	if (parse_move(bb, curr, "e2e4"))
		update_board(bb, curr);

	for (int i = 0; i < TOTAL_BB; i++)
	{
		// after e2e4, only white pawns and WHITE_ALL will change
		if (i == WHITE_PAWNS || i == WHITE_ALL)
			TEST_ASSERT_NOT_EQUAL(bb->pieces[i], copy->pieces[i]);
		else
			TEST_ASSERT_EQUAL(bb->pieces[i], copy->pieces[i]);
	}

	for (int j = 0; j < TOTAL_ATTACKS; j++)
	{
		// don't skip WHITE_PAWNS attacks, because I haven'
		// implemented attack calculation yet.
		TEST_ASSERT_EQUAL(bb->attacks[j], copy->attacks[j]);
	}

	transfer_bb(bb, copy);
	TEST_ASSERT_EQUAL_UINT64_ARRAY(bb->pieces, copy->pieces, TOTAL_BB);
	TEST_ASSERT_EQUAL_UINT64_ARRAY(bb->attacks, copy->attacks, TOTAL_ATTACKS);

	free(bb);
	free(copy);
	free(curr);
	free(prev);
}

void test_update_attacks(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	// I don't need prev for this test
	struct Move *curr = malloc(sizeof(struct Move));
	if (curr == NULL)
	{
		fprintf(stderr, "ERROR: could not allocate enough memory\n");
		exit(EXIT_FAILURE);
	}

	parse_move(bb, curr, "e2e4");
	update_board(bb, curr);

	// update_attacks(bb);

	// after 1. e4, the only attacks which should be updated are
	// white's king, queen, f1 bishop, g1 knight, and pawns.
	// TEST_ASSERT_EQUAL(0x0000000000001010, bb->attacks[WHITE_KING]);
	// TEST_ASSERT_EQUAL(0x0000008040201000, bb->attacks[WHITE_QUEENS]);
	// TEST_ASSERT_EQUAL(0x0000010204081000, bb->attacks[WHITE_BISHOPS]);
	// TEST_ASSERT_EQUAL(0x0000000000A51000, bb->attacks[WHITE_KNIGHTS]);
	// TEST_ASSERT_EQUAL(0x00000038EFFF0000, bb->attacks[WHITE_PAWNS]);

	// black pieces should remain unchanged
	// TEST_ASSERT_EQUAL(0x0000FFFF00000000, bb->attacks[BLACK_PAWNS]);
	// TEST_ASSERT_EQUAL(0x0000A50000000000, bb->attacks[BLACK_KNIGHTS]);
	// TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_BISHOPS]);
	// TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_ROOKS]);
	// TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_QUEENS]);
	// TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_KING]);

	free(bb);
	free(curr);
}

// void test_validate_move(void)
// {
// 	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
// 	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
// 	int turn = BLACK;

// 	free(bb);
// }

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_parse_move);
	RUN_TEST(test_update_board);
	RUN_TEST(test_transfer_move);
	RUN_TEST(test_transfer_bitboards);
	// RUN_TEST(test_update_attacks);
	//RUN_TEST(test_validate_move);

	return UNITY_END();
}