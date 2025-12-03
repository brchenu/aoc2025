import math


def is_odd(val):
    return val % 2 != 0


def count_digits(val):
    return math.floor(math.log10(abs(val))) + 1


with open("day2.txt") as f:
    lines = f.readlines()


def part1(ranges):

    count = 0
    for r in ranges:
        min, max = map(int, r.split("-"))

        for i in range(min, max + 1):
            if is_odd(count_digits(i)):
                continue

            curr = str(i)
            half = len(curr) // 2

            start = curr[:half]
            end = curr[half:]

            if start == end:
                count += i

    return count

def has_repetition(val):
    word = str(val)
    half = len(word) // 2

    for w in reversed(range(1, half + 1)):
        if len(word) % w != 0:  # skip window sizes that don't divide evenly
            continue
        match = word[0:w]
        is_repetition = True
        for j in range(w, len(word), w):
            if match != word[j : j + w]:
                is_repetition = False
                break 
        if is_repetition:
            return True
    return False

def part2(ranges):
    count = 0
    for r in ranges:
        min, max = map(int, r.split('-'))

        for i in range(min, max + 1):
            if(has_repetition(i)):
                count += i

    return count

ranges = lines[0].split(",")

print(f"Day 2 | Part 1 | Python result: {part1(ranges)}")
print(f"Day 2 | Part 2 | Python result: {part2(ranges)}")
