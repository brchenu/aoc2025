with open("day1.txt", "r") as f:
    lines = f.readlines()

count_pt1 = 0
count_pt2 = 0
pos = 50

for line in lines:
    side = line[:1]
    quantity = int(line[1:])

    while quantity > 100:
        quantity -= 100
        count_pt2 += 1

    if side == 'L':
        quantity = -quantity  

    if (pos + quantity > 100 or pos + quantity < 0) and pos != 0:
        count_pt2 += 1

    pos = (pos + quantity) % 100

    if pos == 0:
        count_pt1 += 1

print(f"Day 1 | Part 1 | Python result: {count_pt1}")
print(f"Day 1 | Part 2 | Python result: {count_pt1 + count_pt2}")