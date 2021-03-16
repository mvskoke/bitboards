ls = ["a5", 
      "b5", 
      "a6", 
      "b6", 
      "b7", 
      "c7", 
      "c6", 
      "h5", 
      "g5", 
      "h6", 
      "g6", 
      "g7", 
      "f7", 
      "f6", 
      "a2", 
      "b2", 
      "h2", 
      "g2", 
      "g3", 
      "f3", 
      "f2"]


for coord in ls:
    file = ord(coord[0]) - 97
    rank = int(coord[1]) - 1
    index = file + 8*rank
    #print(f"{coord} {index}")
    print(f"0x{2**index:016x}")