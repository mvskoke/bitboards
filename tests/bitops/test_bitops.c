/** test_bitops.c

Test suite for all basic bitboard operations

*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// -I../../src/
#include "bitboards.h"
#include "colors.h"
#include "display.h"
#include "init.h"

#include "../../unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_set_bit(void)
{
	uint64_t bb = 0;
	TEST_ASSERT_BIT_HIGH(0, set_bit(&bb, 0));
	TEST_ASSERT_BIT_HIGH(1, set_bit(&bb, 1));
	TEST_ASSERT_BIT_HIGH(2, set_bit(&bb, 2));
	TEST_ASSERT_BIT_HIGH(3, set_bit(&bb, 3));
	TEST_ASSERT_BIT_HIGH(4, set_bit(&bb, 4));
	TEST_ASSERT_BIT_HIGH(5, set_bit(&bb, 5));
	TEST_ASSERT_BIT_HIGH(6, set_bit(&bb, 6));
	TEST_ASSERT_BIT_HIGH(7, set_bit(&bb, 7));
	TEST_ASSERT_BIT_HIGH(8, set_bit(&bb, 8));
	TEST_ASSERT_BIT_HIGH(9, set_bit(&bb, 9));
	TEST_ASSERT_BIT_HIGH(10, set_bit(&bb, 10));
	TEST_ASSERT_BIT_HIGH(11, set_bit(&bb, 11));
	TEST_ASSERT_BIT_HIGH(12, set_bit(&bb, 12));
	TEST_ASSERT_BIT_HIGH(13, set_bit(&bb, 13));
	TEST_ASSERT_BIT_HIGH(14, set_bit(&bb, 14));
	TEST_ASSERT_BIT_HIGH(15, set_bit(&bb, 15));
	TEST_ASSERT_BIT_HIGH(16, set_bit(&bb, 16));
	TEST_ASSERT_BIT_HIGH(17, set_bit(&bb, 17));
	TEST_ASSERT_BIT_HIGH(18, set_bit(&bb, 18));
	TEST_ASSERT_BIT_HIGH(19, set_bit(&bb, 19));
	TEST_ASSERT_BIT_HIGH(20, set_bit(&bb, 20));
	TEST_ASSERT_BIT_HIGH(21, set_bit(&bb, 21));
	TEST_ASSERT_BIT_HIGH(22, set_bit(&bb, 22));
	TEST_ASSERT_BIT_HIGH(23, set_bit(&bb, 23));
	TEST_ASSERT_BIT_HIGH(24, set_bit(&bb, 24));
	TEST_ASSERT_BIT_HIGH(25, set_bit(&bb, 25));
	TEST_ASSERT_BIT_HIGH(26, set_bit(&bb, 26));
	TEST_ASSERT_BIT_HIGH(27, set_bit(&bb, 27));
	TEST_ASSERT_BIT_HIGH(28, set_bit(&bb, 28));
	TEST_ASSERT_BIT_HIGH(29, set_bit(&bb, 29));
	TEST_ASSERT_BIT_HIGH(30, set_bit(&bb, 30));
	TEST_ASSERT_BIT_HIGH(31, set_bit(&bb, 31));
	TEST_ASSERT_BIT_HIGH(32, set_bit(&bb, 32));
	TEST_ASSERT_BIT_HIGH(33, set_bit(&bb, 33));
	TEST_ASSERT_BIT_HIGH(34, set_bit(&bb, 34));
	TEST_ASSERT_BIT_HIGH(35, set_bit(&bb, 35));
	TEST_ASSERT_BIT_HIGH(36, set_bit(&bb, 36));
	TEST_ASSERT_BIT_HIGH(37, set_bit(&bb, 37));
	TEST_ASSERT_BIT_HIGH(38, set_bit(&bb, 38));
	TEST_ASSERT_BIT_HIGH(39, set_bit(&bb, 39));
	TEST_ASSERT_BIT_HIGH(40, set_bit(&bb, 40));
	TEST_ASSERT_BIT_HIGH(41, set_bit(&bb, 41));
	TEST_ASSERT_BIT_HIGH(42, set_bit(&bb, 42));
	TEST_ASSERT_BIT_HIGH(43, set_bit(&bb, 43));
	TEST_ASSERT_BIT_HIGH(44, set_bit(&bb, 44));
	TEST_ASSERT_BIT_HIGH(45, set_bit(&bb, 45));
	TEST_ASSERT_BIT_HIGH(46, set_bit(&bb, 46));
	TEST_ASSERT_BIT_HIGH(47, set_bit(&bb, 47));
	TEST_ASSERT_BIT_HIGH(48, set_bit(&bb, 48));
	TEST_ASSERT_BIT_HIGH(49, set_bit(&bb, 49));
	TEST_ASSERT_BIT_HIGH(50, set_bit(&bb, 50));
	TEST_ASSERT_BIT_HIGH(51, set_bit(&bb, 51));
	TEST_ASSERT_BIT_HIGH(52, set_bit(&bb, 52));
	TEST_ASSERT_BIT_HIGH(53, set_bit(&bb, 53));
	TEST_ASSERT_BIT_HIGH(54, set_bit(&bb, 54));
	TEST_ASSERT_BIT_HIGH(55, set_bit(&bb, 55));
	TEST_ASSERT_BIT_HIGH(56, set_bit(&bb, 56));
	TEST_ASSERT_BIT_HIGH(57, set_bit(&bb, 57));
	TEST_ASSERT_BIT_HIGH(58, set_bit(&bb, 58));
	TEST_ASSERT_BIT_HIGH(59, set_bit(&bb, 59));
	TEST_ASSERT_BIT_HIGH(60, set_bit(&bb, 60));
	TEST_ASSERT_BIT_HIGH(61, set_bit(&bb, 61));
	TEST_ASSERT_BIT_HIGH(62, set_bit(&bb, 62));
	TEST_ASSERT_BIT_HIGH(63, set_bit(&bb, 63));

	// all bits have been set
	TEST_ASSERT_EQUAL(UINT64_MAX, bb);
	// now clear every bit
	TEST_ASSERT_EQUAL(0, clear_bits(&bb));
}

void test_flip_bit(void)
{
	uint64_t bb = UINT64_MAX;
	// clear every bit, one-by-one
	TEST_ASSERT_BIT_LOW(0, flip_bit(&bb, 0));
	TEST_ASSERT_BIT_LOW(1, flip_bit(&bb, 1));
	TEST_ASSERT_BIT_LOW(2, flip_bit(&bb, 2));
	TEST_ASSERT_BIT_LOW(3, flip_bit(&bb, 3));
	TEST_ASSERT_BIT_LOW(4, flip_bit(&bb, 4));
	TEST_ASSERT_BIT_LOW(5, flip_bit(&bb, 5));
	TEST_ASSERT_BIT_LOW(6, flip_bit(&bb, 6));
	TEST_ASSERT_BIT_LOW(7, flip_bit(&bb, 7));
	TEST_ASSERT_BIT_LOW(8, flip_bit(&bb, 8));
	TEST_ASSERT_BIT_LOW(9, flip_bit(&bb, 9));
	TEST_ASSERT_BIT_LOW(10, flip_bit(&bb, 10));
	TEST_ASSERT_BIT_LOW(11, flip_bit(&bb, 11));
	TEST_ASSERT_BIT_LOW(12, flip_bit(&bb, 12));
	TEST_ASSERT_BIT_LOW(13, flip_bit(&bb, 13));
	TEST_ASSERT_BIT_LOW(14, flip_bit(&bb, 14));
	TEST_ASSERT_BIT_LOW(15, flip_bit(&bb, 15));
	TEST_ASSERT_BIT_LOW(16, flip_bit(&bb, 16));
	TEST_ASSERT_BIT_LOW(17, flip_bit(&bb, 17));
	TEST_ASSERT_BIT_LOW(18, flip_bit(&bb, 18));
	TEST_ASSERT_BIT_LOW(19, flip_bit(&bb, 19));
	TEST_ASSERT_BIT_LOW(20, flip_bit(&bb, 20));
	TEST_ASSERT_BIT_LOW(21, flip_bit(&bb, 21));
	TEST_ASSERT_BIT_LOW(22, flip_bit(&bb, 22));
	TEST_ASSERT_BIT_LOW(23, flip_bit(&bb, 23));
	TEST_ASSERT_BIT_LOW(24, flip_bit(&bb, 24));
	TEST_ASSERT_BIT_LOW(25, flip_bit(&bb, 25));
	TEST_ASSERT_BIT_LOW(26, flip_bit(&bb, 26));
	TEST_ASSERT_BIT_LOW(27, flip_bit(&bb, 27));
	TEST_ASSERT_BIT_LOW(28, flip_bit(&bb, 28));
	TEST_ASSERT_BIT_LOW(29, flip_bit(&bb, 29));
	TEST_ASSERT_BIT_LOW(30, flip_bit(&bb, 30));
	TEST_ASSERT_BIT_LOW(31, flip_bit(&bb, 31));
	TEST_ASSERT_BIT_LOW(32, flip_bit(&bb, 32));
	TEST_ASSERT_BIT_LOW(33, flip_bit(&bb, 33));
	TEST_ASSERT_BIT_LOW(34, flip_bit(&bb, 34));
	TEST_ASSERT_BIT_LOW(35, flip_bit(&bb, 35));
	TEST_ASSERT_BIT_LOW(36, flip_bit(&bb, 36));
	TEST_ASSERT_BIT_LOW(37, flip_bit(&bb, 37));
	TEST_ASSERT_BIT_LOW(38, flip_bit(&bb, 38));
	TEST_ASSERT_BIT_LOW(39, flip_bit(&bb, 39));
	TEST_ASSERT_BIT_LOW(40, flip_bit(&bb, 40));
	TEST_ASSERT_BIT_LOW(41, flip_bit(&bb, 41));
	TEST_ASSERT_BIT_LOW(42, flip_bit(&bb, 42));
	TEST_ASSERT_BIT_LOW(43, flip_bit(&bb, 43));
	TEST_ASSERT_BIT_LOW(44, flip_bit(&bb, 44));
	TEST_ASSERT_BIT_LOW(45, flip_bit(&bb, 45));
	TEST_ASSERT_BIT_LOW(46, flip_bit(&bb, 46));
	TEST_ASSERT_BIT_LOW(47, flip_bit(&bb, 47));
	TEST_ASSERT_BIT_LOW(48, flip_bit(&bb, 48));
	TEST_ASSERT_BIT_LOW(49, flip_bit(&bb, 49));
	TEST_ASSERT_BIT_LOW(50, flip_bit(&bb, 50));
	TEST_ASSERT_BIT_LOW(51, flip_bit(&bb, 51));
	TEST_ASSERT_BIT_LOW(52, flip_bit(&bb, 52));
	TEST_ASSERT_BIT_LOW(53, flip_bit(&bb, 53));
	TEST_ASSERT_BIT_LOW(54, flip_bit(&bb, 54));
	TEST_ASSERT_BIT_LOW(55, flip_bit(&bb, 55));
	TEST_ASSERT_BIT_LOW(56, flip_bit(&bb, 56));
	TEST_ASSERT_BIT_LOW(57, flip_bit(&bb, 57));
	TEST_ASSERT_BIT_LOW(58, flip_bit(&bb, 58));
	TEST_ASSERT_BIT_LOW(59, flip_bit(&bb, 59));
	TEST_ASSERT_BIT_LOW(60, flip_bit(&bb, 60));
	TEST_ASSERT_BIT_LOW(61, flip_bit(&bb, 61));
	TEST_ASSERT_BIT_LOW(62, flip_bit(&bb, 62));
	TEST_ASSERT_BIT_LOW(63, flip_bit(&bb, 63));
	TEST_ASSERT_EQUAL(0, bb);
}

void test_get_bit(void)
{
	/*
	0x 1    2    3    4    5    6    7    8    9    0    A    B    C    D    E    F
	0b 0001 0010 0011 0100 0101 0110 0111 1000 1001 0000 1010 1011 1100 1101 1110 1111
	MSB 63 ... 0 LSB
	*/
	uint64_t bb = 0x1234567890ABCDEF;
	TEST_ASSERT_EQUAL(1, get_bit(bb, 0));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 1));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 2));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 3));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 4));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 5));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 6));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 7));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 8));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 9));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 10));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 11));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 12));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 13));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 14));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 15));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 16));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 17));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 18));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 19));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 20));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 21));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 22));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 23));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 24));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 25));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 26));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 27));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 28));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 29));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 30));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 31));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 32));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 33));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 34));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 35));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 36));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 37));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 38));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 39));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 40));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 41));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 42));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 43));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 44));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 45));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 46));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 47));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 48));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 49));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 50));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 51));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 52));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 53));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 54));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 55));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 56));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 57));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 58));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 59));
	TEST_ASSERT_EQUAL(1, get_bit(bb, 60));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 61));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 62));
	TEST_ASSERT_EQUAL(0, get_bit(bb, 63));
}

void test_init_bb(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);
	printf("WHITE PAWNS:\n");
	print_bb(bb->pieces[WHITE_PAWNS]);
	printf("WHITE KNIGHTS:\n");
	print_bb(bb->pieces[WHITE_KNIGHTS]);
	printf("WHITE BISHOPS:\n");
	print_bb(bb->pieces[WHITE_BISHOPS]);
	printf("WHITE ROOKS:\n");
	print_bb(bb->pieces[WHITE_ROOKS]);
	printf("WHITE QUEENS:\n");
	print_bb(bb->pieces[WHITE_QUEENS]);
	printf("WHITE KING:\n");
	print_bb(bb->pieces[WHITE_KING]);
	printf("WHITE ALL:\n");
	print_bb(bb->white_all);

	printf("BLACK PAWNS:\n");
	print_bb(bb->pieces[BLACK_PAWNS]);
	printf("BLACK KNIGHTS:\n");
	print_bb(bb->pieces[BLACK_KNIGHTS]);
	printf("BLACK BISHOPS:\n");
	print_bb(bb->pieces[BLACK_BISHOPS]);
	printf("BLACK ROOKS:\n");
	print_bb(bb->pieces[BLACK_ROOKS]);
	printf("BLACK QUEENS:\n");
	print_bb(bb->pieces[BLACK_QUEENS]);
	printf("BLACK KING:\n");
	print_bb(bb->pieces[BLACK_KING]);
	printf("BLACK ALL:\n");
	print_bb(bb->black_all);

	printf("THE ENTIRE BOARD:\n");
	print_bb(bb->white_all | bb->black_all);
	TEST_ASSERT_EQUAL(0xFFFF00000000FFFF, bb->white_all | bb->black_all);

	printf("WHITE PAWN ATTACKS:\n");
	print_bb(bb->attacks[WHITE_PAWNS]);
	printf("WHITE PAWN PUSHES:\n");
	print_bb(bb->w_pawn_pushes);
	printf("WHITE KNIGHT ATTACKS:\n");
	print_bb(bb->attacks[WHITE_KNIGHTS]);
	printf("WHITE BISHOP ATTACKS:\n");
	print_bb(bb->attacks[WHITE_BISHOPS]);
	printf("WHITE ROOK ATTACKS:\n");
	print_bb(bb->attacks[WHITE_ROOKS]);
	printf("WHITE QUEEN ATTACKS:\n");
	print_bb(bb->attacks[WHITE_QUEENS]);
	printf("WHITE KING ATTACKS:\n");
	print_bb(bb->attacks[WHITE_KING]);

	printf("BLACK PAWN ATTACKS:\n");
	print_bb(bb->attacks[BLACK_PAWNS]);
	printf("BLACK PAWN PUSHES:\n");
	print_bb(bb->b_pawn_pushes);
	printf("BLACK KNIGHT ATTACKS:\n");
	print_bb(bb->attacks[BLACK_KNIGHTS]);
	printf("BLACK BISHOP ATTACKS:\n");
	print_bb(bb->attacks[BLACK_BISHOPS]);
	printf("BLACK ROOK ATTACKS:\n");
	print_bb(bb->attacks[BLACK_ROOKS]);
	printf("BLACK QUEEN ATTACKS:\n");
	print_bb(bb->attacks[BLACK_QUEENS]);
	printf("BLACK KING ATTACKS:\n");
	print_bb(bb->attacks[BLACK_KING]);

	free(bb);
}

void test_clear_bit(void)
{
	uint64_t bb = 0;
	TEST_ASSERT_EQUAL(0, clear_bit(&bb, 0));
	TEST_ASSERT_EQUAL(0, clear_bit(&bb, 8));
	TEST_ASSERT_EQUAL(0, clear_bit(&bb, 63));
	TEST_ASSERT_EQUAL(0, clear_bit(&bb, 12));

	bb = UINT64_MAX;
	// ... 1110 1111 1111
	TEST_ASSERT_EQUAL(0xFFFFFFFFFFFFFEFF, clear_bit(&bb, 8));

	bb = UINT64_MAX;
	// 0111 1111 1111 ...
	TEST_ASSERT_EQUAL(0x7FFFFFFFFFFFFFFF, clear_bit(&bb, 63));
	TEST_ASSERT_EQUAL(0x3FFFFFFFFFFFFFFF, clear_bit(&bb, 62));
	TEST_ASSERT_EQUAL(0x1FFFFFFFFFFFFFFF, clear_bit(&bb, 61));
	TEST_ASSERT_EQUAL(0x1FFFFFFFFFFEFFFF, clear_bit(&bb, 16));
	TEST_ASSERT_EQUAL(0x1FFFFFFEFFFEFFFF, clear_bit(&bb, 32));
	TEST_ASSERT_EQUAL(0x1FFFFFFEFFFE7FFF, clear_bit(&bb, 15));
	TEST_ASSERT_EQUAL(0x1FFFFFFEFBFE7FFF, clear_bit(&bb, 26));
	clear_bit(&bb, 28);
	clear_bit(&bb, 29);
	clear_bit(&bb, 53);
	clear_bit(&bb, 42);
	clear_bit(&bb, 43);
	TEST_ASSERT_EQUAL(0x1FDFF3FECBFE7FFF, bb);
	clear_bit(&bb, 19);
	clear_bit(&bb, 34);
	clear_bit(&bb, 40);
	clear_bit(&bb, 47);
	clear_bit(&bb, 48);
	clear_bit(&bb, 3);
	clear_bit(&bb, 4);
	TEST_ASSERT_EQUAL(0x1FDE72FACBF67FE7, bb);

	// ... 1111 1111 1101
	//TEST_ASSERT_EQUAL(0x1FFFFFFFFFFEFFFD, clear_bit(&bb, 1));
	TEST_ASSERT_EQUAL(0, clear_bits(&bb));
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_set_bit);
	RUN_TEST(test_flip_bit);
	RUN_TEST(test_get_bit);
	RUN_TEST(test_init_bb);
	RUN_TEST(test_clear_bit);

	return UNITY_END();
}
