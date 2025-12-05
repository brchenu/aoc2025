def is_odd(val: int) -> bool:
    return val % 2 != 0


def count_digits(val: int) -> int:
    return len(str(abs(val)))


with open("day2.txt") as f:
    lines = f.readlines()


def part1(ranges: list[str]) -> int:
    count = 0
    for r in ranges:
        min_val, max_val = map(int, r.split("-"))

        for i in range(min_val, max_val + 1):
            if is_odd(count_digits(i)):
                continue

            curr = str(i)
            half = len(curr) // 2

            if curr[:half] == curr[half:]:
                count += i

    return count


def has_repetition(val: int) -> bool:
    word = str(val)
    length = len(word)

    for w in reversed(range(1, length // 2 + 1)):
        if length % w != 0:  # skip window sizes that don't divide evenly
            continue
        pattern = word[:w]
        if all(word[j:j + w] == pattern for j in range(w, length, w)):
            return True
    return False


def part2(ranges: list[str]) -> int:
    count = 0
    for r in ranges:
        min_val, max_val = map(int, r.split("-"))

        for i in range(min_val, max_val + 1):
            if has_repetition(i):
                count += i

    return count


ranges = lines[0].split(",")

print(f"Day 2 | Part 1 | Python result: {part1(ranges)}")
print(f"Day 2 | Part 2 | Python result: {part2(ranges)}")
