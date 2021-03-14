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
	struct Move *curr_move = malloc(sizeof(struct Move));
	struct Move *prev_move = malloc(sizeof(struct Move));
	init_moves(curr_move, prev_move);
	// I don't actually test prev_move here, I init it because
	// the init function needs it.

	// it has the exact same implementation as curr_move anyway,
	// so its functionality will be tested when the main program
	// actually needs it.

	// load the ruy lopez
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");

	// morphy defence
	TEST_ASSERT_EQUAL(curr_move, parse_move(bb, curr_move, "a7a6"));
	TEST_ASSERT_EQUAL(A7, curr_move->start);
	TEST_ASSERT_EQUAL(A6, curr_move->end);
	TEST_ASSERT_EQUAL(BLACK_PAWNS, curr_move->piece);
	TEST_ASSERT_EQUAL(BLACK, curr_move->color);

	// berlin defence
	TEST_ASSERT_EQUAL(curr_move, parse_move(bb, curr_move, "g8f6"));
	TEST_ASSERT_EQUAL(G8, curr_move->start);
	TEST_ASSERT_EQUAL(F6, curr_move->end);
	TEST_ASSERT_EQUAL(BLACK_KNIGHTS, curr_move->piece);
	TEST_ASSERT_EQUAL(BLACK, curr_move->color);

	// nothing
	TEST_ASSERT_EQUAL(NULL, parse_move(bb, curr_move, "a3a4"));
	TEST_ASSERT_EQUAL(NULL, parse_move(bb, curr_move, "c5d6"));

	TEST_ASSERT_EQUAL(curr_move, parse_move(bb, curr_move, "d7d6"));
	TEST_ASSERT_EQUAL(D7, curr_move->start);
	TEST_ASSERT_EQUAL(D6, curr_move->end);
	TEST_ASSERT_EQUAL(BLACK_PAWNS, curr_move->piece);
	TEST_ASSERT_EQUAL(BLACK, curr_move->color);

	// promotion (illegal but I have to test it)
	TEST_ASSERT_EQUAL(NONEXISTENT, curr_move->promotion);
	TEST_ASSERT_EQUAL(curr_move, parse_move(bb, curr_move, "d7d8q"));
	TEST_ASSERT_EQUAL(D7, curr_move->start);
	TEST_ASSERT_EQUAL(D8, curr_move->end);
	TEST_ASSERT_EQUAL(BLACK_PAWNS, curr_move->piece);
	TEST_ASSERT_EQUAL(BLACK, curr_move->color);
	TEST_ASSERT_EQUAL(BLACK_QUEENS, curr_move->promotion);

	free(curr_move);
	free(prev_move);
	free(bb);
}

void test_update_board(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	struct Move *curr_move = malloc(sizeof(struct Move));
	struct Move *prev_move = malloc(sizeof(struct Move));
	init_moves(curr_move, prev_move);

	// setting up the ruy lopez
	// 0xFDEF04121020EF9F
	if (parse_move(bb, curr_move, "e2e4")) {
		update_board(bb, curr_move);
		display_move(curr_move);
	}

	if (parse_move(bb, curr_move, "e7e5")) {
		update_board(bb, curr_move);
		display_move(curr_move);
	}

	// non-existent piece
	// ADD CALL TO VALIDATION ONCE THAT'S IMPLEMENTED!!!
	if (parse_move(bb, curr_move, "c5d5")) {
		update_board(bb, curr_move);
		display_move(curr_move);
	}


	/********************************************************

	illegal move -- MUST VALIDATE AFTER PARSING!

	********************************************************/

	// if (parse_move(bb, curr_move, "e1f1")) {
	// 	update_board(bb, curr_move);
	// 	display_move(curr_move);
	// }

	if (parse_move(bb, curr_move, "g1f3")) {
		update_board(bb, curr_move);
		display_move(curr_move);
	}

	if (parse_move(bb, curr_move, "b8c6")) {
		update_board(bb, curr_move);
		display_move(curr_move);
	}

	if (parse_move(bb, curr_move, "f1b5")) {
		update_board(bb, curr_move);
		display_move(curr_move);
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

	printf("********HERE!!!!!!!!!!!!*********\n");
	print_bb(bb->pieces[WHITE]);
	print_bb(bb->pieces[BLACK]);
	print_bb(bb->pieces[WHITE_ALL]);
	print_bb(bb->pieces[BLACK_ALL]);

	TEST_ASSERT_EQUAL(0x1000EF00, bb->pieces[WHITE_PAWNS]);
	TEST_ASSERT_EQUAL(0xFDEF04121020EF9F, bb->pieces[WHITE_ALL] | bb->pieces[BLACK_ALL]);

	free(bb);
	free(curr_move);
	free(prev_move);
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
	struct Move *curr_move = malloc(sizeof(struct Move));
	struct Move *prev_move = malloc(sizeof(struct Move));
	init_moves(curr_move, prev_move);

	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	char command[] = "e2e4";
	do_move(curr_move, prev_move, command, bb);
	strcpy(command, "e7e5");
	do_move(curr_move, prev_move, command, bb);

	printf("***end of test***\ncurr: ");
	display_move(curr_move);  // should be e7e5
	printf("prev: ");
	display_move(prev_move);  // should be e2e4

	free(bb);
	free(curr_move);
	free(prev_move);
}

void test_update_attacks(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	// I don't need prev_move for this test
	struct Move *curr_move = malloc(sizeof(struct Move));
	if (curr_move == NULL)
	{
		fprintf(stderr, "ERROR: could not allocate enough memory\n");
		exit(EXIT_FAILURE);
	}

	parse_move(bb, curr_move, "e2e4");
	update_board(bb, curr_move);

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
	free(curr_move);
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
	// RUN_TEST(test_update_attacks);
	//RUN_TEST(test_validate_move);

	return UNITY_END();
}