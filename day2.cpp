#include <charconv>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

// constexpr digit counting without floating-point precision issues
constexpr int count_digits(long long val) {
    int count = 0;
    val = val < 0 ? -val : val;
    do {
        ++count;
        val /= 10;
    } while (val > 0);
    return count;
}

constexpr bool is_odd(long long val) { return val % 2 != 0; }

// Integer-based power of 10 to avoid std::pow precision issues
constexpr long long pow10(int exp) {
    long long result = 1;
    for (int i = 0; i < exp; ++i)
        result *= 10;
    return result;
}

bool is_repeated_twice(long long val) {
    const int len = count_digits(val);

    if (is_odd(len))
        return false;

    const long long divisor = pow10(len / 2);
    const long long first = val / divisor;
    const long long second = val % divisor;

    return first == second;
}

bool is_repeated(long long val) {
    const auto word = std::to_string(val);
    const auto len = static_cast<int>(word.size());
    const int half = len / 2;

    for (int w = half; w > 0; --w) {
        if (len % w != 0)
            continue;

        const std::string_view match(word.data(), w);
        bool is_repeating = true;

        for (int j = w; j < len; j += w) {
            if (match != std::string_view(word.data() + j, w)) {
                is_repeating = false;
                break;
            }
        }

        if (is_repeating)
            return true;
    }

    return false;
}

// Helper to parse a number from string_view (C++17)
std::optional<long long> parse_number(std::string_view sv) {
    long long value{};
    auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
    if (ec == std::errc{})
        return value;
    return std::nullopt;
}

int main() {
    std::ifstream file("day2.txt");

    if (!file) {
        std::cerr << "Failed to open day2.txt\n";
        return 1;
    }

    std::string line;
    std::getline(file, line);

    long long part1 = 0;
    long long part2 = 0;

    size_t start = 0;
    size_t pos;

    while ((pos = line.find(',', start)) != std::string::npos || start < line.size()) {
        const size_t end = (pos != std::string::npos) ? pos : line.size();
        const std::string_view range_sv(line.data() + start, end - start);

        if (const auto sep = range_sv.find('-'); sep != std::string_view::npos) {
            const auto min = parse_number(range_sv.substr(0, sep));
            const auto max = parse_number(range_sv.substr(sep + 1));

            if (min && max) {
                for (long long i = *min; i <= *max; ++i) {
                    if (is_repeated_twice(i))
                        part1 += i;
                    if (is_repeated(i))
                        part2 += i;
                }
            }
        }

        if (pos == std::string::npos)
            break;
        start = pos + 1;
    }

    std::cout << "Day 2 | Part 1 | C++ result: " << part1 << '\n';
    std::cout << "Day 2 | Part 2 | C++ result: " << part2 << '\n';
    return 0;
}