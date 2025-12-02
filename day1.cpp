#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream file("day1.txt");
    if (!file.is_open()) {
        std::cerr << "Error while opening the file!";
        std::abort();
    }

    std::string line;

    int pos = 50;
    int count_pt1 = 0;
    int count_pt2 = 0;

    while (std::getline(file, line)) {
        char side = line[0];
        int quantity = std::stoi(line.substr(1));

        while (quantity > 100) {
            quantity -= 100;
            count_pt2++;
        }

        if (side == 'L') {
            if (pos - quantity < 0 && pos != 0)
                count_pt2++;

            pos = (pos - quantity) % 100;

            if (pos < 0)
                pos += 100;
        } else {
            if (pos + quantity > 100)
                count_pt2++;

            pos = (pos + quantity) % 100;
        }

        if (pos == 0)
            count_pt1++;
    }

    std::cout << "Day1 | Part1 | C++ result: " << count_pt1 << "\n";
    std::cout << "Day1 | Part2 | C++ result: " << count_pt1 + count_pt2 << "\n";

    return 0;
}