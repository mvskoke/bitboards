#include <stdbool.h>

// -I../../src/
// #include "attacks.h"
// #include "bitboards.h"
#include "chess.h"
// #include "colors.h"
#include "display.h"
#include "init.h"
#include "move.h"
#include "update.h"

#include "../../unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_chess_init(void)
{
	struct Chess *chess = init_chess();
	init_bb(chess->bb);
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

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_chess_init);

	return UNITY_END();
}
