import math


def is_odd(val):
    return val % 2 != 0


def count_digits(val):
    return math.floor(math.log10(abs(val))) + 1


with open("day2.txt") as f:
    lines = f.readlines()


def part1():
    ranges = lines[0].split(",")

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

print(f"Day 2 | Part 1 | Python result: {part1()}")