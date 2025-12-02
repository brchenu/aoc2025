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

bool is_repeated(long long val) {
    int len = count_digits(val);

    if (is_odd(len))
        return false;

    long long pow10 = std::pow(10, (len / 2));

    long long first = val / pow10;
    long long second = val % pow10;

    return first == second;
}

double decimal(double value) {
    int floor = static_cast<int>(value);
    return value - floor;
}

int main() {
    std::ifstream file("day2.txt");
    std::vector<std::pair<int, int>> ranges;

    long long count = 0;
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
                if (is_repeated(i)) {
                    count += i;
                }
            }
        }
    }

    std::cout << "Day 2 | Part 1 | C++ result: " << count << "\n";
    return 0;
}