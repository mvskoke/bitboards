#include <stdbool.h>

// -I../../src/
#include "chess.h"

#include "../../unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_chess_init(void)
{
	struct Chess *chess = init_chess();
	init_bb(chess->bb);
	transfer_bb(chess->bb, chess->copy);

	// ensure transfer was successful
	TEST_ASSERT_EQUAL_UINT64_ARRAY(chess->bb->pieces, chess->copy->pieces, TOTAL_BB);
	TEST_ASSERT_EQUAL_UINT64_ARRAY(chess->bb->attacks, chess->copy->attacks, TOTAL_ATTACKS);
	TEST_ASSERT_EQUAL(chess->bb->white_all, chess->copy->white_all);
	TEST_ASSERT_EQUAL(chess->bb->black_all, chess->copy->black_all);
	TEST_ASSERT_EQUAL(chess->bb->w_pawn_pushes, chess->copy->w_pawn_pushes);
	TEST_ASSERT_EQUAL(chess->bb->b_pawn_pushes, chess->copy->b_pawn_pushes);

	TEST_ASSERT_EQUAL(chess->bb->w_queenside_castle, chess->copy->w_queenside_castle);
	TEST_ASSERT_EQUAL(chess->bb->w_kingside_castle, chess->copy->w_kingside_castle);
	TEST_ASSERT_EQUAL(chess->bb->b_queenside_castle, chess->copy->b_queenside_castle);
	TEST_ASSERT_EQUAL(chess->bb->b_kingside_castle, chess->copy->b_kingside_castle);

	// do this once you go back to cchess:
	// init_bb_fen(chess, "FEN string blblblbl w KQkq etc");
	init_moves(chess->curr, chess->prev);

	chess->ascii = false;
	print_bb_pretty(chess->bb, chess->orient, chess->turn, chess->ascii);

	parse_move(chess->bb, chess->curr, "e2e4");
	TEST_ASSERT_EQUAL(12, chess->curr->start);
	TEST_ASSERT_EQUAL(28, chess->curr->end);
	TEST_ASSERT_EQUAL(WHITE_PAWNS, chess->curr->piece);
	TEST_ASSERT_EQUAL(WHITE, chess->curr->color);
	TEST_ASSERT_EQUAL(OTHER, chess->curr->type);

	update_board(chess->bb, chess->curr);
	chess->turn = !chess->turn;
	print_bb_pretty(chess->bb, chess->orient, chess->turn, chess->ascii);

	destroy_chess(chess);
}

// PLAY A WHOLE GAME
void test_game(void)
{
	struct Chess *chess = init_chess();
	init_bb(chess->bb);
	transfer_bb(chess->bb, chess->copy);
	init_moves(chess->curr, chess->prev);

	destroy_chess(chess);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_chess_init);
	RUN_TEST(test_game);

	return UNITY_END();
}
