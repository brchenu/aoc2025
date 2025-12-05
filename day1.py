with open("day1.txt", "r") as f:
    lines = f.readlines()

INITIAL_POS = 50
MAX_POS = 100

count_pt1 = 0
count_pt2 = 0

pos = INITIAL_POS

for line in lines:
    side, quantity = line[0], int(line[1:])

    while quantity > MAX_POS:
        quantity -= MAX_POS
        count_pt2 += 1

    if side == "L":
        quantity = -quantity

    if (pos + quantity > MAX_POS or pos + quantity < 0) and pos != 0:
        count_pt2 += 1

    pos = (pos + quantity) % MAX_POS

    if pos == 0:
        count_pt1 += 1

print(f"Day 1 | Part 1 | Python result: {count_pt1}")
print(f"Day 1 | Part 2 | Python result: {count_pt1 + count_pt2}")
