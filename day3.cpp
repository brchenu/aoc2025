#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

int main() {
    std::ifstream file("day3.txt");
    if (!file) {
        std::cerr << "Error while opening the file";
        return 1;
    }

    constexpr int REMAINING_CHARS = 11;

    int p1_final_voltage = 0;
    long long p2_final_voltage = 0;

    std::string line;
    while (std::getline(file, line)) {

        auto first_digit = std::max_element(line.begin(), line.end() - 1);
        auto second_digit = std::max_element(first_digit + 1, line.end());

        int voltage = (*first_digit - '0') * 10 + (*second_digit - '0');

        p1_final_voltage += voltage;

        constexpr std::size_t M = 12;
        std::size_t min_pos = 0;

        std::string result;
        result.reserve(M);

        std::string_view line_view(line);

        for (std::size_t remaining = M; remaining > 0; --remaining) {
            std::size_t max_valid_pos = line.size() - remaining;
            std::size_t length = max_valid_pos - min_pos + 1;

            auto subset = line_view.substr(min_pos, length);
            auto max_it = std::max_element(subset.begin(), subset.end());
            
            result.push_back(*max_it);
            min_pos += static_cast<std::size_t>(std::distance(subset.begin(), max_it)) + 1;
        }

        p2_final_voltage += std::stoll(result);
    }

    std::cout << "Day 3 | Part 1 | C++ result: " << p1_final_voltage << "\n";
    std::cout << "Day 3 | Part 2 | C++ result: " << p2_final_voltage << "\n";
    return 0;
}