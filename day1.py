with open("day1.txt", "r") as f:
    lines = f.readlines()

count = 0
pos = 50

for line in lines:
    side = line[:1]
    quantity = int(line[1:])

    if side == 'L':
        quantity = -quantity  

    pos = (pos + quantity) % 100

    if pos == 0:
        count += 1

print(f"Day 1 | Part 1 | Python result: {count}")