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
	init_bb_fen(bb, "rnbqk2r/pp2ppbp/3p1np1/8/3NP3/2N1B3/PPPQ1PPP/R3KB1R");
	TEST_ASSERT_EQUAL(true, safe_path(bb->attacks, BLACK, D1, C1));

	// white's queenside castle is blocked by attack
	init_bb_fen(bb, "r1bq1rk1/1p2pp1p/p1np1npb/8/3NP3/2NQ1P2/PPP2BPP/R3KB1R");
	TEST_ASSERT_EQUAL(false, safe_path(bb->attacks, BLACK, D1, C1));

	/* BLACK castles */
	// black's kingside castle is legal
	init_bb_fen(bb, "rnbqk2r/pp2ppbp/3p1np1/8/3NP3/2N1B3/PPPQ1PPP/R3KB1R");
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

void test_clear_path(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);
	TEST_ASSERT_EQUAL(false, clear_path(bb, F1, G1));
	TEST_ASSERT_EQUAL(false, clear_path(bb, D1, C1));
	TEST_ASSERT_EQUAL(false, clear_path(bb, F8, G8));
	TEST_ASSERT_EQUAL(false, clear_path(bb, B8, C8));

	/* WHITE castles */
	// ruy lopez, berlin defense; white can castle kingside
	init_bb_fen(bb, "r1bqkb1r/pppp1ppp/2n2n2/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	TEST_ASSERT_EQUAL(true, clear_path(bb, F1, G1));

	// another position, white's kingside castle is blocked by attack
	init_bb_fen(bb, "r2qkbnr/p1p2ppp/2pp4/4p3/2b1P3/P1N2N2/1PPP1PPP/R1BQK2R");
	TEST_ASSERT_EQUAL(true, clear_path(bb, F1, G1));

	// white's queenside castle is legal
	init_bb_fen(bb, "rnbqk2r/pp2ppbp/3p1np1/8/3NP3/2N1B3/PPPQ1PPP/R3KB1R");
	TEST_ASSERT_EQUAL(true, clear_path(bb, D1, C1));

	// white's queenside castle is blocked by attack
	init_bb_fen(bb, "r1bq1rk1/1p2pp1p/p1np1npb/8/3NP3/2NQ1P2/PPP2BPP/R3KB1R");
	TEST_ASSERT_EQUAL(true, clear_path(bb, D1, C1));

	/* BLACK castles */
	// black's kingside castle is legal
	init_bb_fen(bb, "rnbqk2r/pp2ppbp/3p1np1/8/3NP3/2N1B3/PPPQ1PPP/R3KB1R");
	TEST_ASSERT_EQUAL(true, clear_path(bb, F8, G8));

	// evans gambit: black's kingside castle is blocked
	init_bb_fen(bb, "r1bqk2r/pppp1ppp/2n2n2/b7/2BpP3/B1P2N2/P4PPP/RN1Q1RK1");
	TEST_ASSERT_EQUAL(true, clear_path(bb, F8, G8));

	// black's queenside castle is open
	init_bb_fen(bb, "r3kbnr/pppbqppp/2np4/4p3/2B1P3/3P1N2/PPP2PPP/RNBQR1K1");
	TEST_ASSERT_EQUAL(true, clear_path(bb, B8, C8));

	// black's queenside castle is open
	init_bb_fen(bb, "r3kbnr/ppp1qppp/2npB3/4p3/4P3/3P1N2/PPP2PPP/RNBQR1K1");
	TEST_ASSERT_EQUAL(true, clear_path(bb, B8, C8));

	// scotch gambit
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/4p3/3PP3/5N2/PPP2PPP/RNBQKB1R");
	TEST_ASSERT_EQUAL(false, clear_path(bb, F1, G1));
	TEST_ASSERT_EQUAL(false, clear_path(bb, D1, C1));
	TEST_ASSERT_EQUAL(false, clear_path(bb, F8, G8));
	TEST_ASSERT_EQUAL(false, clear_path(bb, B8, C8));

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
	// I know it's black's turn but it doesn't matter for this test
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
	init_bb_fen(bb, "rnbqk2r/pp2ppbp/3p1np1/8/3NP3/2N1B3/PPPQ1PPP/R3KB1R");
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

void test_king_in_check(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	// ruy lopez, berlin defence. white to move
	init_bb_fen(bb, "r1bqkb1r/pppp1ppp/2n2n2/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");

	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	TEST_ASSERT_EQUAL(false, king_in_check(bb, WHITE));
	TEST_ASSERT_EQUAL(false, king_in_check(bb, BLACK));

	/* Damiano Defence Demonstration*/
	init_bb_fen(bb, "rnbqkbnr/pppp2pp/8/4p2Q/4P3/8/PPPP1PPP/RNB1KB1R");
	TEST_ASSERT_EQUAL(false, king_in_check(bb, WHITE));
	TEST_ASSERT_EQUAL(true, king_in_check(bb, BLACK));

	// after Qxh5+, g6:
	if (parse_move(bb, curr, "g7g6")) {
		update_board(bb, curr);
		update_attacks(bb);
	}
	TEST_ASSERT_EQUAL(false, king_in_check(bb, WHITE));
	TEST_ASSERT_EQUAL(false, king_in_check(bb, BLACK));

	// Qxe5+
	if (parse_move(bb, curr, "h5e5")) {
		update_board(bb, curr);
		update_attacks(bb);
	}
	TEST_ASSERT_EQUAL(false, king_in_check(bb, WHITE));
	TEST_ASSERT_EQUAL(true, king_in_check(bb, BLACK));

	// Be7
	parse_move(bb, curr, "f8e7");
	update_board(bb, curr);
	update_attacks(bb);
	TEST_ASSERT_EQUAL(false, king_in_check(bb, WHITE));
	TEST_ASSERT_EQUAL(false, king_in_check(bb, BLACK));

	// Qxh8
	parse_move(bb, curr, "e5h8");
	update_board(bb, curr);
	update_attacks(bb);
	TEST_ASSERT_EQUAL(false, king_in_check(bb, WHITE));
	TEST_ASSERT_EQUAL(false, king_in_check(bb, BLACK));

	// Kf8
	parse_move(bb, curr, "e8f8");
	update_board(bb, curr);
	update_attacks(bb);
	TEST_ASSERT_EQUAL(false, king_in_check(bb, WHITE));
	TEST_ASSERT_EQUAL(false, king_in_check(bb, BLACK));

	// f3
	parse_move(bb, curr, "f2f3");
	update_board(bb, curr);
	update_attacks(bb);
	TEST_ASSERT_EQUAL(false, king_in_check(bb, WHITE));
	TEST_ASSERT_EQUAL(false, king_in_check(bb, BLACK));

	// Bh4+
	parse_move(bb, curr, "e7h4");
	update_board(bb, curr);
	update_attacks(bb);
	TEST_ASSERT_EQUAL(true, king_in_check(bb, WHITE));
	TEST_ASSERT_EQUAL(false, king_in_check(bb, BLACK));

	free(bb);
	free(curr);
	free(prev);
}

void test_validate_move1(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb_fen(bb, "5rk1/pp2pp1p/3p2pB/5q2/3b4/2r2P2/PK2QP1P/3R3R");
	enum Color turn = BLACK;

	struct Bitboards *copy = malloc(sizeof(struct Bitboards));
	init_bb(copy);
	transfer_bb(bb, copy);

	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	/* FULL SEQUENCE: Rc2+ Ka3 Qa6+ Kb3 Qxa2+ Kb4 Bc5+ Kb5 a6# */
	/************************** Rc2+ **************************/
	parse_move(bb, curr, "c3c2");
	if (validate_move(bb, copy, curr, turn)) {
		update_board(bb, curr);
		update_attacks(bb);
		TEST_ASSERT_EQUAL(C3, curr->start);
		TEST_ASSERT_EQUAL(C2, curr->end);
		TEST_ASSERT_EQUAL(BLACK_ROOKS, curr->piece);
		TEST_ASSERT_EQUAL(BLACK, curr->color);
		TEST_ASSERT_EQUAL(NONEXISTENT, curr->promotion);
		TEST_ASSERT_EQUAL(OTHER, curr->type);
	}

	/*********!!!!!!!!! DON'T FORGET THIS !!!!!!!!!*********/
	turn = !turn;

	// Kxc2 (illegal)
	parse_move(bb, curr, "b2c2");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	// Qxc2 (illegal because Rxc2 was double check)
	parse_move(bb, curr, "e2c2");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	// Ka1 (illegal)
	parse_move(bb, curr, "b2a1");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	// Kg6 (illegal)
	parse_move(bb, curr, "b2g6");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	// Kb1 (legal)
	parse_move(bb, curr, "b2b1");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	// Kb3 (legal)
	parse_move(bb, curr, "b2b3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	/************************** Ka3 **************************/
	parse_move(bb, curr, "b2a3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	// Kg7 (illegal)
	parse_move(bb, curr, "g8g7");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	// Qe4??? (legal)
	parse_move(bb, curr, "f5e4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	// Qd5 (legal)
	parse_move(bb, curr, "f5d5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	// Qc5 (legal)
	parse_move(bb, curr, "f5c5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	// Kh8 (legal)
	parse_move(bb, curr, "g8h8");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	// Rfc8 (legal)
	parse_move(bb, curr, "f8c8");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	// Rcc8 (legal)
	parse_move(bb, curr, "c2c8");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	/************************** Qa5+ **************************/
	parse_move(bb, curr, "f5a5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	// Kb3 will be the only legal king move
	parse_move(bb, curr, "a3b2");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "a3b4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "a3a4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "a3a2");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "a3a5");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	// other random (and illegal) moves
	parse_move(bb, curr, "e2a4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "h6f8");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d1d4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "h1g1");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f3f4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f3e4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f3a8");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	/************************** Kb3 **************************/
	// Kb3 is the only legal move
	parse_move(bb, curr, "a3b3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	// Rfxf2 (illegal)
	parse_move(bb, curr, "f8f2");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	// Rfc1 (illegal)
	// legal square for other rook but not this one (the f rook)
	parse_move(bb, curr, "f8c1");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	/************************** Qxa2+ **************************/
	parse_move(bb, curr, "a5a2");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	// Qxa2 (illegal)
	parse_move(bb, curr, "e2a2");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	// Kc4
	parse_move(bb, curr, "b3c4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	/************************** Kb4 **************************/
	parse_move(bb, curr, "b3b4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	/************************** Bc5+ **************************/
	parse_move(bb, curr, "d4c5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	// Bxh8 (still illegal)
	parse_move(bb, curr, "h6f8");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);

	/************************** Kb5 **************************/
	parse_move(bb, curr, "b4b5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	/************************** a5# **************************/
	parse_move(bb, curr, "a7a6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	// checkmate, no legal moves
	parse_move(bb, curr, "b5a4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b5b4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b5c4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b5a5");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b5c5");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b5a6");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b5b6");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b5c6");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	free(bb);
	free(copy);
	free(curr);
	free(prev);
}

void test_validate_move2(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);
	enum Color turn = WHITE;

	struct Bitboards *copy = malloc(sizeof(struct Bitboards));
	init_bb(copy);
	transfer_bb(bb, copy);

	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	/* brute force the first 2 plies */

	/************************ WHITE PLY 1 ************************/
	// pawn pushes
	parse_move(bb, curr, "a2a3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b2b3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c2c3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d2d3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e2e3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f2f3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g2g3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "h2h3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "a2a4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b2b4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c2c4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d2d4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e2e4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f2f4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g2g4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "h2h4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	// knights
	parse_move(bb, curr, "b1a3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b1c3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g1f3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g1h3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	parse_move(bb, curr, "e2e4");
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	/************************ BLACK PLY 1 ************************/
	// pawn pushes
	parse_move(bb, curr, "a7a6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b7b6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c7c6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d7d6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e7e6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f7f6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g7g6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "h7h6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "a7a5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b7b5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c7c5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d7d5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e7e5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f7f5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g7g5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "h7h5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	// knights
	parse_move(bb, curr, "b8a6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b8c6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g8f6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g8h6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	parse_move(bb, curr, "e7e5");
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	/************************ WHITE PLY 2 ************************/
	// pawn pushes
	parse_move(bb, curr, "a2a3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b2b3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c2c3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d2d3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f2f3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g2g3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "h2h3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "a2a4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b2b4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c2c4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d2d4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f2f4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g2g4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "h2h4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	// knights
	parse_move(bb, curr, "b1a3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b1c3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g1f3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g1h3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	// light square bishop on f1
	parse_move(bb, curr, "f1e2");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f1d3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f1c4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f1b5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f1a6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	// dark square bishop on c1
	parse_move(bb, curr, "c1e2");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c1d3");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c1c4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c1b5");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c1a6");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	// queen
	parse_move(bb, curr, "d1e2");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d1f3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d1g4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d1h5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	// Qxe1
	parse_move(bb, curr, "d1e1");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	// king
	parse_move(bb, curr, "e1e2");  // Ke2!!!!#
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	// Ke3?
	parse_move(bb, curr, "e1e3");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	// castle
	parse_move(bb, curr, "e1g1");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e1c1");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	parse_move(bb, curr, "g1f3");
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	free(bb);
	free(copy);
	free(curr);
	free(prev);
}

void test_validate_move3(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);
	enum Color turn = WHITE;

	struct Bitboards *copy = malloc(sizeof(struct Bitboards));
	init_bb(copy);
	transfer_bb(bb, copy);

	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	/* let's play out the scotch gambit */
	parse_move(bb, curr, "e2e4");
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	parse_move(bb, curr, "e7e5");
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	parse_move(bb, curr, "g1f3");
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	parse_move(bb, curr, "b8c6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	parse_move(bb, curr, "d2d4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	parse_move(bb, curr, "d7d6");  // horrible move
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e5e4");  // e4
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f8c5");  // Bc5
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f8c4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e8g8");  // 0-0
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e8c8");  // 0-0-0
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	parse_move(bb, curr, "e5d4");  // exd4
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	parse_move(bb, curr, "d4d5");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c2c3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f3d4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d1d4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e1g1");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e1g1");  // 0-0
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e1c1");  // 0-0-0
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	// try to queenside castle the other color
	parse_move(bb, curr, "e8c8");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	parse_move(bb, curr, "f1c4");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	parse_move(bb, curr, "d4d3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g8f6");  // best response to the gambit
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f8e7");  // Be7
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "g8e7");  // Ne7
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f8a3");  // free bishop
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "a8b8");  // Rb8????
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "f8c4");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e8e7");  // Ke7!!!!#
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	parse_move(bb, curr, "f8c5");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	parse_move(bb, curr, "d1d4");  // free queen
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e1g1");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	parse_move(bb, curr, "c2c3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	parse_move(bb, curr, "g8f6");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "d4d3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "c5f2");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));

	parse_move(bb, curr, "d4c3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	parse_move(bb, curr, "e1g1");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e1c1");
	TEST_ASSERT_EQUAL(false, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "b1c3");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	// parse_move(bb, curr,)

	parse_move(bb, curr, "c4f7");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	// position after Bxf7+
	TEST_ASSERT_EQUAL(0xDDCF040400040000, bb->black_all);
	TEST_ASSERT_EQUAL(0x002000001020E39F, bb->white_all);
	TEST_ASSERT_EQUAL(0xDDEF04041024E39F, bb->all);

	parse_move(bb, curr, "e8f8");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	parse_move(bb, curr, "e8e7");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));

	TEST_ASSERT_EQUAL(true, bb->b_kingside_castle);
	TEST_ASSERT_EQUAL(true, bb->b_queenside_castle);

	parse_move(bb, curr, "e8f7");
	TEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));
	update_board(bb, curr);
	update_attacks(bb);
	turn = !turn;

	TEST_ASSERT_EQUAL(false, bb->b_kingside_castle);
	TEST_ASSERT_EQUAL(false, bb->b_queenside_castle);

	// position after Kxf7
	TEST_ASSERT_EQUAL(0xCDEF040400040000, bb->black_all);
	TEST_ASSERT_EQUAL(0x000000001020E39F, bb->white_all);
	TEST_ASSERT_EQUAL(0xCDEF04041024E39F, bb->all);

	free(bb);
	free(copy);
	free(curr);
	free(prev);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_validate_pawn_move);
	RUN_TEST(test_attacks_set);
	RUN_TEST(test_safe_path);
	RUN_TEST(test_clear_path);
	RUN_TEST(test_validate_king_move);
	RUN_TEST(test_king_in_check);
	RUN_TEST(test_validate_move1);
	RUN_TEST(test_validate_move2);
	RUN_TEST(test_validate_move3);

	return UNITY_END();
}
