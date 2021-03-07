# quickly generate a 64-bit num to represent a bitboard when
# given the bit indexes to set

total = 0
n = int(input(">>> ").strip())
while n != -1:
    total += 2 ** n
    n = int(input(">>> ").strip())

print(f"0x{total:x}")