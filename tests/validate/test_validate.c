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
	init_bb(bb);
	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	/* pawn pushes */
	parse_move(bb, curr, "a2a3");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "b2b3");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "c2c3");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "d2d3");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "e2e3");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "f2f3");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "g2g3");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "h2h3");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "a2a4");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "b2b4");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "c2c4");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "d2d4");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "e2e4");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "f2f4");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "g2g4");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "h2h4");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));

	/* pawn captures */
	// all illegal in the starting position
	parse_move(bb, curr, "a2b3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	parse_move(bb, curr, "b2a3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "b2c3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	parse_move(bb, curr, "c2b3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "c2d3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	parse_move(bb, curr, "d2c3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "d2e3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	parse_move(bb, curr, "e2d3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "e2f3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	parse_move(bb, curr, "f2e3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "f2g3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	parse_move(bb, curr, "g2f3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "g2h3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	parse_move(bb, curr, "h2g3");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	/* ridiculous captures */
	parse_move(bb, curr, "e2e8");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "d2e7");
	TEST_ASSERT_EQUAL(false, validate_pawn_move(bb, curr));

	/* test a FEN position */
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");

	/* pawn pushes */
	parse_move(bb, curr, "a7a6");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "d7d6");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "d7d5");
	TEST_ASSERT_EQUAL(true, validate_pawn_move(bb, curr));
	parse_move(bb, curr, "h7h5");
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

void test_attacks_set(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	// ruy lopez, after Bb5
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");

	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	// pseudo-legal moves
	parse_move(bb, curr, "g8f6"); // Nf6
	TEST_ASSERT_EQUAL(true, attacks_set(bb, curr));
	parse_move(bb, curr, "f8c5"); // Bc5
	TEST_ASSERT_EQUAL(true, attacks_set(bb, curr));
	parse_move(bb, curr, "f8b4"); // Bb4
	TEST_ASSERT_EQUAL(true, attacks_set(bb, curr));
	parse_move(bb, curr, "f8e7"); // Be7
	TEST_ASSERT_EQUAL(true, attacks_set(bb, curr));
	parse_move(bb, curr, "e8e7"); // Ke7!!!!
	TEST_ASSERT_EQUAL(true, attacks_set(bb, curr));
	parse_move(bb, curr, "c6b8"); // Nb8
	TEST_ASSERT_EQUAL(true, attacks_set(bb, curr));

	// illegal moves
	parse_move(bb, curr, "c6e5"); // Nxe5
	TEST_ASSERT_EQUAL(false, attacks_set(bb, curr));
	parse_move(bb, curr, "f8c6"); // Bxc6
	TEST_ASSERT_EQUAL(false, attacks_set(bb, curr));
	parse_move(bb, curr, "c6b5"); // Nxb5
	TEST_ASSERT_EQUAL(false, attacks_set(bb, curr));

	free(bb);
	free(curr);
	free(prev);
}

void test_safe_path(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));

	/* WHITE castles */
	// ruy lopez, berlin defense; white can castle kingside
	init_bb_fen(bb, "r1bqkb1r/pppp1ppp/2n2n2/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	TEST_ASSERT_EQUAL(true, safe_path(bb->attacks, BLACK, F1, G1));

	// another position, white's kingside castle is blocked by attack
	init_bb_fen(bb, "r2qkbnr/p1p2ppp/2pp4/4p3/2b1P3/P1N2N2/1PPP1PPP/R1BQK2R");
	TEST_ASSERT_EQUAL(false, safe_path(bb->attacks, BLACK, F1, G1));

	// white's queenside castle is legal
	init_bb_fen(bb, "rnbq1rk1/pp2ppbp/3p1np1/8/3NP3/2N1B3/PPPQ1PPP/R3KB1R");
	TEST_ASSERT_EQUAL(true, safe_path(bb->attacks, BLACK, D1, C1));

	// white's queenside castle is blocked by attack
	init_bb_fen(bb, "r1bq1rk1/1p2pp1p/p1np1npb/8/3NP3/2NQ1P2/PPP2BPP/R3KB1R");
	TEST_ASSERT_EQUAL(false, safe_path(bb->attacks, BLACK, D1, C1));

	/* BLACK castles */
	// black's kingside castle is legal
	init_bb_fen(bb, "rnbq1rk1/pp2ppbp/3p1np1/8/3NP3/2N1B3/PPPQ1PPP/R3KB1R");
	TEST_ASSERT_EQUAL(true, safe_path(bb->attacks, WHITE, F8, G8));

	// evans gambit: black's kingside castle is blocked
	init_bb_fen(bb, "r1bqk2r/pppp1ppp/2n2n2/b7/2BpP3/B1P2N2/P4PPP/RN1Q1RK1");
	TEST_ASSERT_EQUAL(false, safe_path(bb->attacks, WHITE, F8, G8));

	// black's queenside castle is legal
	init_bb_fen(bb, "r3kbnr/pppbqppp/2np4/4p3/2B1P3/3P1N2/PPP2PPP/RNBQR1K1");
	TEST_ASSERT_EQUAL(true, safe_path(bb->attacks, WHITE, B8, C8));

	// black's queenside castle is blocked
	init_bb_fen(bb, "r3kbnr/ppp1qppp/2npB3/4p3/4P3/3P1N2/PPP2PPP/RNBQR1K1");
	TEST_ASSERT_EQUAL(false, safe_path(bb->attacks, WHITE, B8, C8));

	free(bb);
}

void test_validate_king_move(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	// only check fully legal moves, NO PSEUDO-LEGAL MOVES
	// this routine does NOT know to see if king would be in check
	// after the move (unless it's castling)

	/* WHITE king moves */
	// test the same positions as test_safe_path();
	// legal moves: castle, Ke2, Kf1
	init_bb_fen(bb, "r1bqkb1r/pppp1ppp/2n2n2/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	parse_move(bb, curr, "e1g1");
	TEST_ASSERT_EQUAL(true, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1e2");
	TEST_ASSERT_EQUAL(true, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1f1");
	TEST_ASSERT_EQUAL(true, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1f2");
	TEST_ASSERT_EQUAL(false, validate_king_move(bb, curr));

	// legal moves: none
	init_bb_fen(bb, "r2qkbnr/p1p2ppp/2pp4/4p3/2b1P3/P1N2N2/1PPP1PPP/R1BQK2R");
	parse_move(bb, curr, "e1g1");
	TEST_ASSERT_EQUAL(false, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1f2");
	TEST_ASSERT_EQUAL(false, validate_king_move(bb, curr));

	// legal moves: castle, Ke2, Kd1
	init_bb_fen(bb, "rnbq1rk1/pp2ppbp/3p1np1/8/3NP3/2N1B3/PPPQ1PPP/R3KB1R");
	parse_move(bb, curr, "e1c1");
	TEST_ASSERT_EQUAL(true, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1e2");
	TEST_ASSERT_EQUAL(true, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1d1");
	TEST_ASSERT_EQUAL(true, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1d2");
	TEST_ASSERT_EQUAL(false, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1f1");
	TEST_ASSERT_EQUAL(false, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1f2");
	TEST_ASSERT_EQUAL(false, validate_king_move(bb, curr));

	// legal moves: Ke2, Kd1
	init_bb_fen(bb, "r1bq1rk1/1p2pp1p/p1np1npb/8/3NP3/2NQ1P2/PPP2BPP/R3KB1R");
	parse_move(bb, curr, "e1c1");
	TEST_ASSERT_EQUAL(false, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1e2");
	TEST_ASSERT_EQUAL(true, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1d1");
	TEST_ASSERT_EQUAL(true, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1f1");
	TEST_ASSERT_EQUAL(false, validate_king_move(bb, curr));

	parse_move(bb, curr, "e1f2");
	TEST_ASSERT_EQUAL(false, validate_king_move(bb, curr));

	free(bb);
	free(curr);
	free(prev);
}

/*
void test_validate_move(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	enum Color turn = BLACK;

	free(bb);
}
*/
int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_validate_pawn_move);
	RUN_TEST(test_attacks_set);
	RUN_TEST(test_safe_path);
	RUN_TEST(test_validate_king_move);
	// RUN_TEST(test_validate_move);

	return UNITY_END();
}