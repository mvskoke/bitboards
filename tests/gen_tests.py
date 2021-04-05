def gen_massive_test():
    for i in range(64):
        print(f"TEST_ASSERT_EQUAL({2**i}, set_bit(&bb, {i}));\nTEST_ASSERT_BIT_LOW({i}, flip_bit(&bb, {i}));\nTEST_ASSERT_BIT_HIGH({i}, set_bit(&bb, {i}));\nclear_bits(&bb);")
        print()

def gen_small_tests():
    for i in range(64):
        print(f"TEST_ASSERT_BIT_HIGH({i}, set_bit(&bb, {i}));")
        #print()

def gen_flips():
    for i in range(64):
        print(f"TEST_ASSERT_BIT_LOW({i}, flip_bit(&bb, {i}));")

def gen_123():
    num = "0001001000110100010101100111100010010000101010111100110111101111"
    num_str = num[::-1]
    for i in range(64):
        if num_str[i] == '0':
            print(f"TEST_ASSERT_EQUAL(0, get_bit(bb, {i}));")
        else:
            print(f"TEST_ASSERT_EQUAL(1, get_bit(bb, {i}));")

def gen_squares():
    files = "abcdefgh"
    ranks = "12345678"
    i = 0
    for r in ranks:
        for f in files:
            print(f"TEST_ASSERT_EQUAL({i}, get_sq_index(\"{f}{r}\"));")
            i+=1

def gen_pawn_pushes():
    files = "abcdefgh"
    ranks = "34"
    for r in ranks:
        for f in files:
            print(f"parse_move(bb, curr, \"{f}2{f}{r}\");\nTEST_ASSERT_EQUAL(true, validate_move(bb, copy, curr, turn));")

if __name__ == "__main__":
    gen_pawn_pushes()