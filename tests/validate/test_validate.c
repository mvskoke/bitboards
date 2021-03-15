/** test_validate.c

Test suite for testing move validation

*/

#include <stdio.h>
#include <stdlib.h>

#include "../../src/bitboards.h"
#include "../../src/colors.h"
#include "../../src/init.h"
#include "../../src/update.h"
#include "../../src/move.h"

#include "../../unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

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

	// RUN_TEST(test_validate_move);

	return UNITY_END();
}