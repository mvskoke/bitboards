/** test_attacks.c

Test suite for attack calculation

*/

#include <stdio.h>
#include <stdlib.h>

#include "../../src/attacks.h"
#include "../../src/bitboards.h"
#include "../../src/colors.h"
#include "../../src/init.h"
#include "../../src/move.h"
#include "../../src/update.h"

#include "../../unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_knight_attack(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	// triple fork position
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	/* from FEN position */

	// white knight on e5
	TEST_ASSERT_EQUAL(0x0028440004280000, knight_attack(bb->pieces[WHITE_KNIGHTS], bb->white_all));
	// black knight on d5
	TEST_ASSERT_EQUAL(0x0010000022140000, knight_attack(bb->pieces[BLACK_KNIGHTS], bb->black_all));

	if (parse_move(bb, curr, "e5d7"))
		update_board(bb, curr);

	TEST_ASSERT_EQUAL(0x2200221400000000, knight_attack(bb->pieces[WHITE_KNIGHTS], bb->white_all));

	/* from more FEN positions */
	// ruy lopez
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	TEST_ASSERT_EQUAL(0x0000005088050040, knight_attack(bb->pieces[WHITE_KNIGHTS], bb->white_all));
	TEST_ASSERT_EQUAL(0x0210A0010A000000, knight_attack(bb->pieces[BLACK_KNIGHTS], bb->black_all));

	// (5:10) https://www.youtube.com/watch?v=FiVm9me72oA
	init_bb_fen(bb, "6k1/5p2/pn1p4/N2p2p1/PP1Pp2q/1BrbP1QP/6K1/4R3");
	TEST_ASSERT_EQUAL(0x0002040004000000, knight_attack(bb->pieces[WHITE_KNIGHTS], bb->white_all));
	TEST_ASSERT_EQUAL(0x0508000005000000, knight_attack(bb->pieces[BLACK_KNIGHTS], bb->black_all));

	/* knight pairs */
	// starting squares
	TEST_ASSERT_EQUAL(0x0000000000A51800, knight_attack(0x0000000000000042, 0));
	TEST_ASSERT_EQUAL(0x0018A50000000000, knight_attack(0x4200000000000000, 0));
	// a5 b5
	TEST_ASSERT_EQUAL(0x0002040004020000 | 0x0005080008050000, knight_attack(0x0000000300000000, 0));
	// e5 g1
	TEST_ASSERT_EQUAL(0x0028440044A81000, knight_attack(0x0000001000000040, 0));
	// e5 d3
	TEST_ASSERT_EQUAL(0x0028441466282214, knight_attack(0x0000001000080000, 0));

	/* lone knights */
	TEST_ASSERT_EQUAL(0x0028440044280000, knight_attack(0x0000001000000000, 0));  //e5
	TEST_ASSERT_EQUAL(0x00000A1100110A00, knight_attack(0x0000000004000000, 0));  //c4

	TEST_ASSERT_EQUAL(0x0002040004020000, knight_attack(0x0000000100000000, 0));  //a5
	TEST_ASSERT_EQUAL(0x0005080008050000, knight_attack(0x0000000200000000, 0));  //b5
	TEST_ASSERT_EQUAL(0x0204000402000000, knight_attack(0x0000010000000000, 0));  //a6
	TEST_ASSERT_EQUAL(0x0508000805000000, knight_attack(0x0000020000000000, 0));  //b6
	TEST_ASSERT_EQUAL(0x0800080500000000, knight_attack(0x0002000000000000, 0));  //b7
	TEST_ASSERT_EQUAL(0x1100110A00000000, knight_attack(0x0004000000000000, 0));  //c7
	TEST_ASSERT_EQUAL(0x0A1100110A000000, knight_attack(0x0000040000000000, 0));  //c6

	TEST_ASSERT_EQUAL(0x0040200020400000, knight_attack(0x0000008000000000, 0));  //h5
	TEST_ASSERT_EQUAL(0x00A0100010A00000, knight_attack(0x0000004000000000, 0));  //g5
	TEST_ASSERT_EQUAL(0x4020002040000000, knight_attack(0x0000800000000000, 0));  //h6
	TEST_ASSERT_EQUAL(0xA0100010A0000000, knight_attack(0x0000400000000000, 0));  //g6
	TEST_ASSERT_EQUAL(0x100010A000000000, knight_attack(0x0040000000000000, 0));  //g7
	TEST_ASSERT_EQUAL(0x8800885000000000, knight_attack(0x0020000000000000, 0));  //f7
	TEST_ASSERT_EQUAL(0x5088008850000000, knight_attack(0x0000200000000000, 0));  //f6

	TEST_ASSERT_EQUAL(0x0000000002040004, knight_attack(0x0000000000000100, 0));  //a2
	TEST_ASSERT_EQUAL(0x0000000005080008, knight_attack(0x0000000000000200, 0));  //b2
	TEST_ASSERT_EQUAL(0x0000000040200020, knight_attack(0x0000000000008000, 0));  //h2
	TEST_ASSERT_EQUAL(0x00000000A0100010, knight_attack(0x0000000000004000, 0));  //g2
	TEST_ASSERT_EQUAL(0x000000A0100010A0, knight_attack(0x0000000000400000, 0));  //g3
	TEST_ASSERT_EQUAL(0x0000005088008850, knight_attack(0x0000000000200000, 0));  //f3
	TEST_ASSERT_EQUAL(0x0000000050880088, knight_attack(0x0000000000002000, 0));  //f2

	free(bb);
	free(curr);
	free(prev);
}

void test_king_attack(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));

	/* from FEN positions */
	// triple fork position
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	TEST_ASSERT_EQUAL(0x0000000000001808, king_attack(bb->pieces[WHITE_KING], bb->white_all));
	TEST_ASSERT_EQUAL(0x0A08000000000000, king_attack(bb->pieces[BLACK_KING], bb->black_all));

	// cool mate position
	init_bb_fen(bb, "5rk1/1p2pp1p/p2p2pB/1Kb5/8/5P2/q1r1QP1P/3R3R");
	TEST_ASSERT_EQUAL(0x0000070507000000, king_attack(bb->pieces[WHITE_KING], bb->white_all));
	TEST_ASSERT_EQUAL(0x8040000000000000, king_attack(bb->pieces[BLACK_KING], bb->black_all));

	// deep blue vs kasparov, 1997 game 2 after 36 ... axb5
	init_bb_fen(bb, "r1r1q1k1/6p1/3b1p1p/1p1PpP2/1Pp5/2P4P/R1B2QP1/R5K1");
	TEST_ASSERT_EQUAL(0x00000000000080A0, king_attack(bb->pieces[WHITE_KING], bb->white_all));
	TEST_ASSERT_EQUAL(0xA0A0000000000000, king_attack(bb->pieces[BLACK_KING], bb->black_all));

	// ruy lopez
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	TEST_ASSERT_EQUAL(0x0000000000001020, king_attack(bb->pieces[WHITE_KING], bb->white_all));
	TEST_ASSERT_EQUAL(0x0010000000000000, king_attack(bb->pieces[BLACK_KING], bb->black_all));

	/* from empty bitboards */
	TEST_ASSERT_EQUAL(0x0000030203000000, king_attack(0x0000000100000000, 0));  //a5
	TEST_ASSERT_EQUAL(0x0000C040C0000000, king_attack(0x0000008000000000, 0));  //h5
	TEST_ASSERT_EQUAL(0x0000000000000302, king_attack(0x0000000000000001, 0));  //a1
	TEST_ASSERT_EQUAL(0x000000000000C040, king_attack(0x0000000000000080, 0));  //h1
	TEST_ASSERT_EQUAL(0x0203000000000000, king_attack(0x0100000000000000, 0));  //a8
	TEST_ASSERT_EQUAL(0x40C0000000000000, king_attack(0x8000000000000000, 0));  //h8

	// starting positions
	TEST_ASSERT_EQUAL(0x0000000000003828, king_attack(0x0000000000000010, 0));  // e1
	TEST_ASSERT_EQUAL(0x2838000000000000, king_attack(0x1000000000000000, 0));  // e8

	free(bb);
}

void test_pawn_attack(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));

	/* from FEN positions */
	// triple fork position
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	TEST_ASSERT_EQUAL(0x0000000720600000, pawn_attack(bb->pieces[WHITE_PAWNS], bb->white_all, WHITE));
	TEST_ASSERT_EQUAL(0x00000D0000280000, pawn_attack(bb->pieces[BLACK_PAWNS], bb->black_all, BLACK));

	// after 1. g3 g6 2. Bg2 Bg7 3. b3 b6 4. Bb2 Bb7
	init_bb_fen(bb, "rn1qk1nr/pbppppbp/1p4p1/8/8/1P4P1/PBPPPPBP/RN1QK1NR");
	TEST_ASSERT_EQUAL(0x00000000A53C0000, pawn_attack(bb->pieces[WHITE_PAWNS], bb->white_all, WHITE));
	TEST_ASSERT_EQUAL(0x00003CA500000000, pawn_attack(bb->pieces[BLACK_PAWNS], bb->black_all, BLACK));

	// cool mate position
	init_bb_fen(bb, "5rk1/1p2pp1p/p2p2pB/1Kb5/8/5P2/q1r1QP1P/3R3R");
	TEST_ASSERT_EQUAL(0x0000000050500000, pawn_attack(bb->pieces[WHITE_PAWNS], bb->white_all, WHITE));
	TEST_ASSERT_EQUAL(0x000034B200000000, pawn_attack(bb->pieces[BLACK_PAWNS], bb->black_all, BLACK));

	// deep blue vs kasparov, 1997 game 2 after 36 ... axb5
	init_bb_fen(bb, "r1r1q1k1/6p1/3b1p1p/1p1PpP2/1Pp5/2P4P/R1B2QP1/R5K1");
	TEST_ASSERT_EQUAL(0x0000540548200000, pawn_attack(bb->pieces[WHITE_PAWNS], bb->white_all, WHITE));
	TEST_ASSERT_EQUAL(0x00000040290A0000, pawn_attack(bb->pieces[BLACK_PAWNS], bb->black_all, BLACK));

	// ruy lopez
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	TEST_ASSERT_EQUAL(0x0000002800DF0000, pawn_attack(bb->pieces[WHITE_PAWNS], bb->white_all, WHITE));
	TEST_ASSERT_EQUAL(0x0000FB0028000000, pawn_attack(bb->pieces[BLACK_PAWNS], bb->black_all, BLACK));

	/* from empty bitboards */
	// after 1. e4 e5
	TEST_ASSERT_EQUAL(0x0000002800FF0000, pawn_attack(0x000000001000EF00, 0, WHITE));
	TEST_ASSERT_EQUAL(0x0000FF0028000000, pawn_attack(0x00EF001000000000, 0, BLACK));

	// two connected juicers on the 6th
	// or if it's black, two pawns still on the 2nd
	TEST_ASSERT_EQUAL(0x0700000000000000, pawn_attack(0x0003000000000000, 0, WHITE));
	TEST_ASSERT_EQUAL(0x0000070000000000, pawn_attack(0x0003000000000000, 0, BLACK));

	// a7 h7
	TEST_ASSERT_EQUAL(0x4200000000000000, pawn_attack(0x0081000000000000, 0, WHITE));
	// a6 h6
	TEST_ASSERT_EQUAL(0x0042000000000000, pawn_attack(0x0000810000000000, 0, WHITE));

	// insane chess puzzle (for engines)
	// (48:48) https://www.youtube.com/watch?v=15nuJdAUW0s
	TEST_ASSERT_EQUAL(0x000040AA55000000, pawn_attack(0x00000080542A0000, 0, WHITE));
	TEST_ASSERT_EQUAL(0x00000040AA550000, pawn_attack(0x000080542A000000, 0, BLACK));

	free(bb);
}

void test_pawn_push(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));

	/* from FEN positions */
	// triple fork position
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	TEST_ASSERT_EQUAL(0x00000003A4600000, pawn_push(bb->pieces[WHITE_PAWNS], bb->all, WHITE));
	TEST_ASSERT_EQUAL(0x0000050500000000, pawn_push(bb->pieces[BLACK_PAWNS], bb->all, BLACK));

	// after 1. g3 g6 2. Bg2 Bg7 3. b3 b6 4. Bb2 Bb7
	init_bb_fen(bb, "rn1qk1nr/pbppppbp/1p4p1/8/8/1P4P1/PBPPPPBP/RN1QK1NR");
	TEST_ASSERT_EQUAL(0x00000000FFBD0000, pawn_push(bb->pieces[WHITE_PAWNS], bb->all, WHITE));
	TEST_ASSERT_EQUAL(0x0000BDFF00000000, pawn_push(bb->pieces[BLACK_PAWNS], bb->all, BLACK));

	// cool mate position
	init_bb_fen(bb, "5rk1/1p2pp1p/p2p2pB/1Kb5/8/5P2/q1r1QP1P/3R3R");
	TEST_ASSERT_EQUAL(0x00000000A0800000, pawn_push(bb->pieces[WHITE_PAWNS], bb->all, WHITE));
	TEST_ASSERT_EQUAL(0x0000327900000000, pawn_push(bb->pieces[BLACK_PAWNS], bb->all, BLACK));

	// deep blue vs kasparov, 1997 game 2 after 36 ... axb5
	init_bb_fen(bb, "r1r1q1k1/6p1/3b1p1p/1p1PpP2/1Pp5/2P4P/R1B2QP1/R5K1");
	TEST_ASSERT_EQUAL(0x00000000C0400000, pawn_push(bb->pieces[WHITE_PAWNS], bb->all, WHITE));
	TEST_ASSERT_EQUAL(0x000040C010000000, pawn_push(bb->pieces[BLACK_PAWNS], bb->all, BLACK));

	// ruy lopez
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	TEST_ASSERT_EQUAL(0x00000000CFCF0000, pawn_push(bb->pieces[WHITE_PAWNS], bb->all, WHITE));
	TEST_ASSERT_EQUAL(0x0000EBE900000000, pawn_push(bb->pieces[BLACK_PAWNS], bb->all, BLACK));

	/* from empty bitboards */
	// starting position
	TEST_ASSERT_EQUAL(0x00000000FFFF0000, pawn_push(0x000000000000FF00, 0, WHITE));
	TEST_ASSERT_EQUAL(0x0000FFFF00000000, pawn_push(0x00FF000000000000, 0, BLACK));

	// swap black and white pawns' starting ranks --------------> BELOW -> !!!!!
	TEST_ASSERT_EQUAL(0x00000000000000FF, pawn_push(0x000000000000FF00, 0, BLACK));
	TEST_ASSERT_EQUAL(0xFF00000000000000, pawn_push(0x00FF000000000000, 0, WHITE));

	// insane chess puzzle (for engines)
	// (48:48) https://www.youtube.com/watch?v=15nuJdAUW0s
	TEST_ASSERT_EQUAL(0x000080542A000000, pawn_push(0x00000080542A0000, 0, WHITE));
	TEST_ASSERT_EQUAL(0x00000080542A0000, pawn_push(0x000080542A000000, 0, BLACK));

	free(bb);
}

void test_bishop_attack(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));

	/* from FEN positions */
	// triple fork position
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	TEST_ASSERT_EQUAL(0, bishop_attack(bb->pieces[WHITE_BISHOPS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x0000000508000000, bishop_attack(bb->pieces[BLACK_BISHOPS], bb->black_all, bb->white_all));

	// cool mate position
	init_bb_fen(bb, "5rk1/1p2pp1p/p2p2pB/1Kb5/8/5P2/q1r1QP1P/3R3R");
	TEST_ASSERT_EQUAL(0x2040004020100804, bishop_attack(bb->pieces[WHITE_BISHOPS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x000102000A112000, bishop_attack(bb->pieces[BLACK_BISHOPS], bb->black_all, bb->white_all));

	// after 1. g3 g6 2. Bg2 Bg7 3. b3 b6 4. Bb2 Bb7
	init_bb_fen(bb, "rn1qk1nr/pbppppbp/1p4p1/8/8/1P4P1/PBPPPPBP/RN1QK1NR");
	TEST_ASSERT_EQUAL(0x0042241818A50024, bishop_attack(bb->pieces[WHITE_BISHOPS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x2400A51818244200, bishop_attack(bb->pieces[BLACK_BISHOPS], bb->black_all, bb->white_all));

	// deep blue vs kasparov, 1997 game 2 after 36 ... axb5
	init_bb_fen(bb, "r1r1q1k1/6p1/3b1p1p/1p1PpP2/1Pp5/2P4P/R1B2QP1/R5K1");
	TEST_ASSERT_EQUAL(0x00000000110A000A, bishop_attack(bb->pieces[WHITE_BISHOPS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x2214000402000000, bishop_attack(bb->pieces[BLACK_BISHOPS], bb->black_all, bb->white_all));

	// ruy lopez
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	TEST_ASSERT_EQUAL(0x0000050005081020, bishop_attack(bb->pieces[WHITE_BISHOPS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x0010080402010000, bishop_attack(bb->pieces[BLACK_BISHOPS], bb->black_all, bb->white_all));

	/* from starting position */
	TEST_ASSERT_EQUAL(0x0, bishop_attack(0x0000000000000024, 0x000000000000FFFF, 0xFFFF000000000000));
	TEST_ASSERT_EQUAL(0x0, bishop_attack(0x2400000000000000, 0xFFFF000000000000, 0x000000000000FFFF));

	/* from empty bitboards */
	// 1 bishop
	TEST_ASSERT_EQUAL(0x8041221400142241, bishop_attack(0x0000000008000000, 0, 0));

	// 4 corners
	// a8
	TEST_ASSERT_EQUAL(0x0002040810204080, bishop_attack(0x0100000000000000, 0x0100000000000000, 0));
	// h8
	TEST_ASSERT_EQUAL(0x0040201008040201, bishop_attack(0x8000000000000000, 0x8000000000000000, 0));
	// a1
	TEST_ASSERT_EQUAL(0x8040201008040200, bishop_attack(0x0000000000000001, 0x0000000000000001, 0));
	// h1
	TEST_ASSERT_EQUAL(0x0102040810204000, bishop_attack(0x0000000000000080, 0x0000000000000080, 0));

	// 2 bishops
	// same color square
	// c4, g6
	TEST_ASSERT_EQUAL(0x50A011AA100A1522, bishop_attack(0x0000400004000000, 0x0000400004000000, 0));

	// diff color squares
	// greek gift: e2, h7
	TEST_ASSERT_EQUAL(0x4000C061321C0416, bishop_attack(0x0080000000000800, 0x0080000000000800, 0));
	// filthy london system: d3, f4
	TEST_ASSERT_EQUAL(0x0284C97214509C26, bishop_attack(0x0000000020080000, 0x0000000020080000, 0));

	free(bb);
}

void test_rook_attack(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));

	/* from FEN positions */
	// triple fork position
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	TEST_ASSERT_EQUAL(0x00000000000004CB, rook_attack(bb->pieces[WHITE_ROOKS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0xD820000000000000, rook_attack(bb->pieces[BLACK_ROOKS], bb->black_all, bb->white_all));

	// cool mate position
	init_bb_fen(bb, "5rk1/1p2pp1p/p2p2pB/1Kb5/8/5P2/q1r1QP1P/3R3R");
	TEST_ASSERT_EQUAL(0x0000080808080877, rook_attack(bb->pieces[WHITE_ROOKS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x1F00000004041A04, rook_attack(bb->pieces[BLACK_ROOKS], bb->black_all, bb->white_all));

	// pedro damiano's mate-in-3 puzzle from wikipedia
	init_bb_fen(bb, "kr5r/p7/8/8/4q3/8/1R3Q2/KR6");
	TEST_ASSERT_EQUAL(0x0202020202021DFC, rook_attack(bb->pieces[WHITE_ROOKS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x7C82828282828280, rook_attack(bb->pieces[BLACK_ROOKS], bb->black_all, bb->white_all));

	// deep blue vs kasparov, 1997 game 2 after 36 ... axb5
	init_bb_fen(bb, "r1r1q1k1/6p1/3b1p1p/1p1PpP2/1Pp5/2P4P/R1B2QP1/R5K1");
	TEST_ASSERT_EQUAL(0x010101010101023E, rook_attack(bb->pieces[WHITE_ROOKS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x0A05050501010100, rook_attack(bb->pieces[BLACK_ROOKS], bb->black_all, bb->white_all));

	// ruy lopez
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	TEST_ASSERT_EQUAL(0x60, rook_attack(bb->pieces[WHITE_ROOKS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x0200000000000000, rook_attack(bb->pieces[BLACK_ROOKS], bb->black_all, bb->white_all));

	/* from starting position */
	TEST_ASSERT_EQUAL(0x0, rook_attack(0x0000000000000081, 0x000000000000FFFF, 0xFFFF000000000000));
	TEST_ASSERT_EQUAL(0x0, rook_attack(0x8100000000000000, 0xFFFF000000000000, 0x000000000000FFFF));

	/* from empty bitboards */
	// 1 rook
	// d4
	TEST_ASSERT_EQUAL(0x08080808F7080808, rook_attack(0x0000000008000000, 0x0000000008000000, 0));
	// e8
	TEST_ASSERT_EQUAL(0xEF10101010101010, rook_attack(0x1000000000000000, 0x1000000000000000, 0));
	// f1
	TEST_ASSERT_EQUAL(0x20202020202020DF, rook_attack(0x0000000000000020, 0x0000000000000020, 0));

	// 4 corners
	// a8
	TEST_ASSERT_EQUAL(0xFE01010101010101, rook_attack(0x0100000000000000, 0x0100000000000000, 0));
	// h8
	TEST_ASSERT_EQUAL(0x7F80808080808080, rook_attack(0x8000000000000000, 0x8000000000000000, 0));
	// a1
	TEST_ASSERT_EQUAL(0x01010101010101FE, rook_attack(0x0000000000000001, 0x0000000000000001, 0));
	// h1
	TEST_ASSERT_EQUAL(0x808080808080807F, rook_attack(0x0000000000000080, 0x0000000000000080, 0));

	// 2 rooks
	// c4 g6
	TEST_ASSERT_EQUAL(0x4444BF44FB444444, rook_attack(0x0000400004000000, 0x0000400004000000, 0));

	// a1 h8
	TEST_ASSERT_EQUAL(0x7F818181818181FE, rook_attack(0x8000000000000001, 0x8000000000000001, 0));
	// a8 h1
	TEST_ASSERT_EQUAL(0xFE8181818181817F, rook_attack(0x0100000000000080, 0x0100000000000080, 0));

	// corner on same rank
	// a1 h1
	TEST_ASSERT_EQUAL(0x818181818181817E, rook_attack(0x0000000000000081, 0x0000000000000081, 0));
	// a8 h8
	TEST_ASSERT_EQUAL(0x7E81818181818181, rook_attack(0x8100000000000000, 0x8100000000000000, 0));

	free(bb);
}

void test_queen_attack(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));

	/* from FEN positions */
	// triple fork position
	init_bb_fen(bb, "2k2r2/ppp5/1b3q2/3nN3/PP1Pp1Q1/2P1P2P/5PP1/2R1KR2");
	TEST_ASSERT_EQUAL(0x444850E0B0601008, queen_attack(bb->pieces[WHITE_QUEENS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x8870DC70A0202000, queen_attack(bb->pieces[BLACK_QUEENS], bb->black_all, bb->white_all));

	// cool mate position
	init_bb_fen(bb, "5rk1/1p2pp1p/p2p2pB/1Kb5/8/5P2/q1r1QP1P/3R3R");
	TEST_ASSERT_EQUAL(0x0010101014180C30, queen_attack(bb->pieces[WHITE_QUEENS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x0000100905030203, queen_attack(bb->pieces[BLACK_QUEENS], bb->black_all, bb->white_all));

	// deep blue vs kasparov, 1997 game 2 after 36 ... axb5
	init_bb_fen(bb, "r1r1q1k1/6p1/3b1p1p/1p1PpP2/1Pp5/2P4P/R1B2QP1/R5K1");
	TEST_ASSERT_EQUAL(0x00010204A8701830, queen_attack(bb->pieces[WHITE_QUEENS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x2838548000000000, queen_attack(bb->pieces[BLACK_QUEENS], bb->black_all, bb->white_all));

	// ruy lopez
	init_bb_fen(bb, "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R");
	TEST_ASSERT_EQUAL(0x0000000000001000, queen_attack(bb->pieces[WHITE_QUEENS], bb->white_all, bb->black_all));
	TEST_ASSERT_EQUAL(0x0010204080000000, queen_attack(bb->pieces[BLACK_QUEENS], bb->black_all, bb->white_all));

	// no queens
	TEST_ASSERT_EQUAL(0, queen_attack(0, 23482234895, 903285329058));

	/* from empty bitboards */
	// 1 queen

	// d4
	TEST_ASSERT_EQUAL(0x88492A1CF71C2A49, queen_attack(0x0000000008000000, 0x0000000008000000, 0));

	// 4 corners
	// a8
	TEST_ASSERT_EQUAL(0xFE03050911214181, queen_attack(0x0100000000000000, 0x0100000000000000, 0));
	// h8
	TEST_ASSERT_EQUAL(0x7FC0A09088848281, queen_attack(0x8000000000000000, 0x8000000000000000, 0));
	// a1
	TEST_ASSERT_EQUAL(0x81412111090503FE, queen_attack(0x0000000000000001, 0x0000000000000001, 0));
	// h1
	TEST_ASSERT_EQUAL(0x8182848890A0C07F, queen_attack(0x0000000000000080, 0x0000000000000080, 0));

	// 2 queens

	// opposite corners
	// a1 h8
	TEST_ASSERT_EQUAL(0x7FC1A191898583FE, queen_attack(0x8000000000000001, 0x8000000000000001, 0));
	// a8 h1
	TEST_ASSERT_EQUAL(0xFE83858991A1C17F, queen_attack(0x0100000000000080, 0x0100000000000080, 0));

	// corner on same rank
	// a1 h1
	TEST_ASSERT_EQUAL(0x81C3A59999A5C37E, queen_attack(0x0000000000000081, 0x0000000000000081, 0));
	// a8 h8
	TEST_ASSERT_EQUAL(0x7EC3A59999A5C381, queen_attack(0x8100000000000000, 0x8100000000000000, 0));

	// corner on same file
	// a1 a8
	TEST_ASSERT_EQUAL(0xFE432519192543FE, queen_attack(0x0100000000000001, 0x0100000000000001, 0));

	// same rank
	// a6 h6
	TEST_ASSERT_EQUAL(0xA5C37EC3A59999A5, queen_attack(0x0000810000000000, 0x0000810000000000, 0));
	// c4 f4
	TEST_ASSERT_EQUAL(0x6624BD7EDB7EBD24, queen_attack(0x0000000024000000, 0x0000000024000000, 0));

	// same file
	// e8 e1
	TEST_ASSERT_EQUAL(0xEF385493935438EF, queen_attack(0x1000000000000010, 0x1000000000000010, 0));
	// b6 b3
	TEST_ASSERT_EQUAL(0x4A27FD0F0FFD274A, queen_attack(0x0000020000020000, 0x0000020000020000, 0));

	// other
	// c5 f4
	TEST_ASSERT_EQUAL(0x2635AEFBDF75AC64, queen_attack(0x0000000420000000, 0x0000000420000000, 0));
	// f3 h5
	TEST_ASSERT_EQUAL(0xB1A2E47FF0DFF0A8, queen_attack(0x0000008000200000, 0x0000008000200000, 0));

	// 3 queens
	// a8 c3 e4
	TEST_ASSERT_EQUAL(0xFED7753DEFFB5F97, queen_attack(0x0100000010040000, 0x0100000010040000, 0));

	free(bb);
}

void test_update_attacks(void)
{
	struct Bitboards *bb = malloc(sizeof(struct Bitboards));
	init_bb(bb);
	struct Move *curr = malloc(sizeof(struct Move));
	struct Move *prev = malloc(sizeof(struct Move));
	init_moves(curr, prev);

	if (parse_move(bb, curr, "e2e4"))
		update_board(bb, curr);

	update_attacks(bb);

	TEST_ASSERT_EQUAL(0x0000002800FF0000, bb->attacks[WHITE_PAWNS]);
	TEST_ASSERT_EQUAL(0x00000010EFEF0000, bb->w_pawn_pushes);
	TEST_ASSERT_EQUAL(0x0000000000A51000, bb->attacks[WHITE_KNIGHTS]);
	TEST_ASSERT_EQUAL(0x0000010204081000, bb->attacks[WHITE_BISHOPS]);
	TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[WHITE_ROOKS]);
	TEST_ASSERT_EQUAL(0x0000008040201000, bb->attacks[WHITE_QUEENS]);
	TEST_ASSERT_EQUAL(0x0000000000001000, bb->attacks[WHITE_KING]);

	TEST_ASSERT_EQUAL(0x0000FF0000000000, bb->attacks[BLACK_PAWNS]);
	TEST_ASSERT_EQUAL(0x0000FFFF00000000, bb->b_pawn_pushes);
	TEST_ASSERT_EQUAL(0x0000A50000000000, bb->attacks[BLACK_KNIGHTS]);
	TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_BISHOPS]);
	TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_ROOKS]);
	TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_QUEENS]);
	TEST_ASSERT_EQUAL(0x0000000000000000, bb->attacks[BLACK_KING]);

	// do ruy lopez
	parse_move(bb, curr, "e7e5");
	update_board(bb, curr);
	parse_move(bb, curr, "g1f3");
	update_board(bb, curr);
	parse_move(bb, curr, "b8c6");
	update_board(bb, curr);
	parse_move(bb, curr, "f1b5");
	update_board(bb, curr);

	update_attacks(bb);

	TEST_ASSERT_EQUAL(0x0000002800DF0000, bb->attacks[WHITE_PAWNS]);
	TEST_ASSERT_EQUAL(0x00000000CFCF0000, bb->w_pawn_pushes);
	TEST_ASSERT_EQUAL(0x0000005088050040, bb->attacks[WHITE_KNIGHTS]);
	TEST_ASSERT_EQUAL(0x0000050005081020, bb->attacks[WHITE_BISHOPS]);
	TEST_ASSERT_EQUAL(0x0000000000000060, bb->attacks[WHITE_ROOKS]);
	TEST_ASSERT_EQUAL(0x0000000000001000, bb->attacks[WHITE_QUEENS]);
	TEST_ASSERT_EQUAL(0x0000000000001020, bb->attacks[WHITE_KING]);

	TEST_ASSERT_EQUAL(0x0000FB0028000000, bb->attacks[BLACK_PAWNS]);
	TEST_ASSERT_EQUAL(0x0000EBE900000000, bb->b_pawn_pushes);
	TEST_ASSERT_EQUAL(0x0210A0010A000000, bb->attacks[BLACK_KNIGHTS]);
	TEST_ASSERT_EQUAL(0x0010080402010000, bb->attacks[BLACK_BISHOPS]);
	TEST_ASSERT_EQUAL(0x0200000000000000, bb->attacks[BLACK_ROOKS]);
	TEST_ASSERT_EQUAL(0x0010204080000000, bb->attacks[BLACK_QUEENS]);
	TEST_ASSERT_EQUAL(0x0010000000000000, bb->attacks[BLACK_KING]);

	free(bb);
	free(curr);
	free(prev);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_knight_attack);
	RUN_TEST(test_king_attack);
	RUN_TEST(test_pawn_attack);
	RUN_TEST(test_pawn_push);
	RUN_TEST(test_bishop_attack);
	RUN_TEST(test_rook_attack);
	RUN_TEST(test_queen_attack);
	RUN_TEST(test_update_attacks);

	return UNITY_END();
}