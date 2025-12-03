#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int count_digits(long long val) {
    return std::floor(std::log10(std::abs(val))) + 1;
}

bool is_odd(long long val) { return val % 2 != 0; }

bool is_repeated_twice(long long val) {
    int len = count_digits(val);

    if (is_odd(len))
        return false;

    long long pow10 = std::pow(10, (len / 2));

    long long first = val / pow10;
    long long second = val % pow10;

    return first == second;
}

bool is_repeated(long long val) {
    int len = count_digits(val);

    int half = len / 2;

    std::string word = std::to_string(val);

    for (int w = half; w > 0; --w) {
        if (len % w != 0)
            continue;
        std::string match = word.substr(0, w);
        bool is_repeting = true;
        for (int j = w; j < len; j += w) {
            if (match != word.substr(j, w)) {
                is_repeting = false;
                break;
            }
        }

        if (is_repeting)
            return true;
    }

    return false;
}

int main() {
    std::ifstream file("day2.txt");
    std::vector<std::pair<int, int>> ranges;

    long long part1 = 0;
    long long part2 = 0;

    if (file) {
        std::string line;
        std::getline(file, line);

        line.push_back(','); // To get the last range

        size_t start = 0;
        size_t pos;

        while ((pos = line.find(',', start)) != std::string::npos) {
            size_t len = pos - start;
            std::string range = line.substr(start, len);
            start = pos + 1;

            size_t separator_pos = range.find('-');
            len = range.size() - separator_pos;

            std::string str_min = range.substr(0, separator_pos);
            std::string str_max = range.substr(separator_pos + 1);

            long long min = std::stoll(str_min);
            long long max = std::stoll(str_max);

            for (long long i = min; i <= max; i++) {
                // Part 1
                if (is_repeated_twice(i)) {
                    part1 += i;
                }
                // Part 2
                if (is_repeated(i)) {
                    part2 += i;
                }
            }
        }
    }

    std::cout << "Day 2 | Part 1 | C++ result: " << part1 << "\n";
    std::cout << "Day 2 | Part 2 | C++ result: " << part2 << "\n";
    return 0;
}