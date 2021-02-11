#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../unity/unity.h"
#include "../src/bb.h"

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
	TEST_ASSERT_EQUAL(0, clear_bb(&bb));
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

void test_print_bb(void)
{
	uint64_t bb = 0x55AA55AA55AA55AA;
	print_bb(bb);

	bb = 0xFF00FF00FF00FF00;
	print_bb(bb);
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
	print_bb(bb->pieces[WHITE_ALL]);

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
	print_bb(bb->pieces[BLACK_ALL]);

	printf("THE ENTIRE BOARD:\n");
	print_bb(bb->pieces[WHITE_ALL] | bb->pieces[BLACK_ALL]);
	TEST_ASSERT_EQUAL(0xFFFF00000000FFFF, bb->pieces[WHITE_ALL] | bb->pieces[BLACK_ALL]);

	printf("WHITE PAWN MOVES:\n");
	print_bb(bb->attacks[WHITE_PAWNS]);
	printf("WHITE KNIGHT MOVES:\n");
	print_bb(bb->attacks[WHITE_KNIGHTS]);
	printf("WHITE BISHOP MOVES:\n");
	print_bb(bb->attacks[WHITE_BISHOPS]);
	printf("WHITE ROOK MOVES:\n");
	print_bb(bb->attacks[WHITE_ROOKS]);
	printf("WHITE QUEEN MOVES:\n");
	print_bb(bb->attacks[WHITE_QUEENS]);
	printf("WHITE KING MOVES:\n");
	print_bb(bb->attacks[WHITE_KING]);

	printf("BLACK PAWN MOVES:\n");
	print_bb(bb->attacks[BLACK_PAWNS]);
	printf("BLACK KNIGHT MOVES:\n");
	print_bb(bb->attacks[BLACK_KNIGHTS]);
	printf("BLACK BISHOP MOVES:\n");
	print_bb(bb->attacks[BLACK_BISHOPS]);
	printf("BLACK ROOK MOVES:\n");
	print_bb(bb->attacks[BLACK_ROOKS]);
	printf("BLACK QUEEN MOVES:\n");
	print_bb(bb->attacks[BLACK_QUEENS]);
	printf("BLACK KING MOVES:\n");
	print_bb(bb->attacks[BLACK_KING]);

	free(bb);
}

void test_get_sq_index(void)
{
	TEST_ASSERT_EQUAL(0, get_sq_index("a1"));
	TEST_ASSERT_EQUAL(1, get_sq_index("b1"));
	TEST_ASSERT_EQUAL(2, get_sq_index("c1"));
	TEST_ASSERT_EQUAL(3, get_sq_index("d1"));
	TEST_ASSERT_EQUAL(4, get_sq_index("e1"));
	TEST_ASSERT_EQUAL(5, get_sq_index("f1"));
	TEST_ASSERT_EQUAL(6, get_sq_index("g1"));
	TEST_ASSERT_EQUAL(7, get_sq_index("h1"));
	TEST_ASSERT_EQUAL(8, get_sq_index("a2"));
	TEST_ASSERT_EQUAL(9, get_sq_index("b2"));
	TEST_ASSERT_EQUAL(10, get_sq_index("c2"));
	TEST_ASSERT_EQUAL(11, get_sq_index("d2"));
	TEST_ASSERT_EQUAL(12, get_sq_index("e2"));
	TEST_ASSERT_EQUAL(13, get_sq_index("f2"));
	TEST_ASSERT_EQUAL(14, get_sq_index("g2"));
	TEST_ASSERT_EQUAL(15, get_sq_index("h2"));
	TEST_ASSERT_EQUAL(16, get_sq_index("a3"));
	TEST_ASSERT_EQUAL(17, get_sq_index("b3"));
	TEST_ASSERT_EQUAL(18, get_sq_index("c3"));
	TEST_ASSERT_EQUAL(19, get_sq_index("d3"));
	TEST_ASSERT_EQUAL(20, get_sq_index("e3"));
	TEST_ASSERT_EQUAL(21, get_sq_index("f3"));
	TEST_ASSERT_EQUAL(22, get_sq_index("g3"));
	TEST_ASSERT_EQUAL(23, get_sq_index("h3"));
	TEST_ASSERT_EQUAL(24, get_sq_index("a4"));
	TEST_ASSERT_EQUAL(25, get_sq_index("b4"));
	TEST_ASSERT_EQUAL(26, get_sq_index("c4"));
	TEST_ASSERT_EQUAL(27, get_sq_index("d4"));
	TEST_ASSERT_EQUAL(28, get_sq_index("e4"));
	TEST_ASSERT_EQUAL(29, get_sq_index("f4"));
	TEST_ASSERT_EQUAL(30, get_sq_index("g4"));
	TEST_ASSERT_EQUAL(31, get_sq_index("h4"));
	TEST_ASSERT_EQUAL(32, get_sq_index("a5"));
	TEST_ASSERT_EQUAL(33, get_sq_index("b5"));
	TEST_ASSERT_EQUAL(34, get_sq_index("c5"));
	TEST_ASSERT_EQUAL(35, get_sq_index("d5"));
	TEST_ASSERT_EQUAL(36, get_sq_index("e5"));
	TEST_ASSERT_EQUAL(37, get_sq_index("f5"));
	TEST_ASSERT_EQUAL(38, get_sq_index("g5"));
	TEST_ASSERT_EQUAL(39, get_sq_index("h5"));
	TEST_ASSERT_EQUAL(40, get_sq_index("a6"));
	TEST_ASSERT_EQUAL(41, get_sq_index("b6"));
	TEST_ASSERT_EQUAL(42, get_sq_index("c6"));
	TEST_ASSERT_EQUAL(43, get_sq_index("d6"));
	TEST_ASSERT_EQUAL(44, get_sq_index("e6"));
	TEST_ASSERT_EQUAL(45, get_sq_index("f6"));
	TEST_ASSERT_EQUAL(46, get_sq_index("g6"));
	TEST_ASSERT_EQUAL(47, get_sq_index("h6"));
	TEST_ASSERT_EQUAL(48, get_sq_index("a7"));
	TEST_ASSERT_EQUAL(49, get_sq_index("b7"));
	TEST_ASSERT_EQUAL(50, get_sq_index("c7"));
	TEST_ASSERT_EQUAL(51, get_sq_index("d7"));
	TEST_ASSERT_EQUAL(52, get_sq_index("e7"));
	TEST_ASSERT_EQUAL(53, get_sq_index("f7"));
	TEST_ASSERT_EQUAL(54, get_sq_index("g7"));
	TEST_ASSERT_EQUAL(55, get_sq_index("h7"));
	TEST_ASSERT_EQUAL(56, get_sq_index("a8"));
	TEST_ASSERT_EQUAL(57, get_sq_index("b8"));
	TEST_ASSERT_EQUAL(58, get_sq_index("c8"));
	TEST_ASSERT_EQUAL(59, get_sq_index("d8"));
	TEST_ASSERT_EQUAL(60, get_sq_index("e8"));
	TEST_ASSERT_EQUAL(61, get_sq_index("f8"));
	TEST_ASSERT_EQUAL(62, get_sq_index("g8"));
	TEST_ASSERT_EQUAL(63, get_sq_index("h8"));
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
	TEST_ASSERT_EQUAL(0, clear_bb(&bb));
}

void test_get_piece_type(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);
	TEST_ASSERT_EQUAL(WHITE_PAWN, get_piece_type(bb, "a2"));
	TEST_ASSERT_EQUAL(WHITE_PAWN, get_piece_type(bb, "b2"));
	TEST_ASSERT_EQUAL(WHITE_PAWN, get_piece_type(bb, "c2"));
	TEST_ASSERT_EQUAL(WHITE_PAWN, get_piece_type(bb, "d2"));
	TEST_ASSERT_EQUAL(WHITE_PAWN, get_piece_type(bb, "e2"));
	TEST_ASSERT_EQUAL(WHITE_PAWN, get_piece_type(bb, "f2"));
	TEST_ASSERT_EQUAL(WHITE_PAWN, get_piece_type(bb, "g2"));
	TEST_ASSERT_EQUAL(WHITE_PAWN, get_piece_type(bb, "h2"));

	TEST_ASSERT_EQUAL(BLACK_PAWN, get_piece_type(bb, "a7"));
	TEST_ASSERT_EQUAL(BLACK_PAWN, get_piece_type(bb, "b7"));
	TEST_ASSERT_EQUAL(BLACK_PAWN, get_piece_type(bb, "c7"));
	TEST_ASSERT_EQUAL(BLACK_PAWN, get_piece_type(bb, "d7"));
	TEST_ASSERT_EQUAL(BLACK_PAWN, get_piece_type(bb, "e7"));
	TEST_ASSERT_EQUAL(BLACK_PAWN, get_piece_type(bb, "f7"));
	TEST_ASSERT_EQUAL(BLACK_PAWN, get_piece_type(bb, "g7"));
	TEST_ASSERT_EQUAL(BLACK_PAWN, get_piece_type(bb, "h7"));

	// this should never happen for real
	// but im testing anyway to make sure it works
	TEST_ASSERT_EQUAL(NONEXISTENT, get_piece_type(bb, "e3"));
	TEST_ASSERT_EQUAL(NONEXISTENT, get_piece_type(bb, "a5"));
	TEST_ASSERT_EQUAL(NONEXISTENT, get_piece_type(bb, "b5"));
	TEST_ASSERT_EQUAL(NONEXISTENT, get_piece_type(bb, "c5"));
	TEST_ASSERT_EQUAL(NONEXISTENT, get_piece_type(bb, "d5"));
	TEST_ASSERT_EQUAL(NONEXISTENT, get_piece_type(bb, "e5"));
	TEST_ASSERT_EQUAL(NONEXISTENT, get_piece_type(bb, "f5"));
	TEST_ASSERT_EQUAL(NONEXISTENT, get_piece_type(bb, "g5"));
	TEST_ASSERT_EQUAL(NONEXISTENT, get_piece_type(bb, "h5"));

	TEST_ASSERT_EQUAL(WHITE_ROOK, get_piece_type(bb, "a1"));
	TEST_ASSERT_EQUAL(WHITE_KNIGHT, get_piece_type(bb, "b1"));
	TEST_ASSERT_EQUAL(WHITE_BISHOP, get_piece_type(bb, "c1sdfsdjflk"));
	TEST_ASSERT_EQUAL(WHITE_QUEEN, get_piece_type(bb, "d1"));
	TEST_ASSERT_EQUAL(WHITE_KING, get_piece_type(bb, "e1"));
	TEST_ASSERT_EQUAL(WHITE_BISHOP, get_piece_type(bb, "f1"));
	TEST_ASSERT_EQUAL(WHITE_KNIGHT, get_piece_type(bb, "g101010110101010101000"));
	TEST_ASSERT_EQUAL(WHITE_ROOK, get_piece_type(bb, "h1"));

	TEST_ASSERT_EQUAL(BLACK_ROOK, get_piece_type(bb, "a8"));
	TEST_ASSERT_EQUAL(BLACK_KNIGHT, get_piece_type(bb, "b8"));
	TEST_ASSERT_EQUAL(BLACK_BISHOP, get_piece_type(bb, "c8"));
	TEST_ASSERT_EQUAL(BLACK_QUEEN, get_piece_type(bb, "d8"));
	TEST_ASSERT_EQUAL(BLACK_KING, get_piece_type(bb, "e8"));
	TEST_ASSERT_EQUAL(BLACK_BISHOP, get_piece_type(bb, "f8"));
	TEST_ASSERT_EQUAL(BLACK_KNIGHT, get_piece_type(bb, "g8"));
	TEST_ASSERT_EQUAL(BLACK_ROOK, get_piece_type(bb, "h8"));

	free(bb);
}

void test_update_board(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);

	// ruy lopez = 0xFDEF04121020EF9F
	update_board(bb, "e2e4");
	update_board(bb, "e7e5");
	update_board(bb, "g1f3");
	update_board(bb, "b8c6");
	update_board(bb, "f1b5");

	//print_bb(bb->pieces[WHITE_ALL] | bb->pieces[BLACK_ALL]);
	//print_all_bb(bb);
	print_bb_pretty(bb, BLACK, WHITE);
	print_bb_small(bb);
	TEST_ASSERT_EQUAL(0x1000EF00, bb->pieces[WHITE_PAWNS]);
	TEST_ASSERT_EQUAL(0xFDEF04121020EF9F, bb->pieces[WHITE_ALL] | bb->pieces[BLACK_ALL]);
	free(bb);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_set_bit);
	RUN_TEST(test_flip_bit);
	RUN_TEST(test_get_bit);
	//RUN_TEST(test_print_bb);
	RUN_TEST(test_init_bb);
	RUN_TEST(test_get_sq_index);
	RUN_TEST(test_clear_bit);
	RUN_TEST(test_get_piece_type);
	RUN_TEST(test_update_board);
	return UNITY_END();
}
