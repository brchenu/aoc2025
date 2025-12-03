#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    constexpr int LOCK_LENGTH = 100;
    constexpr int START_POS = 50;

    std::ifstream file("day1.txt");
    if (!file) {
        std::cerr << "Error while opening the file!";
        return 1;
    }

    std::string line;

    int pos = START_POS;
    int count_pt1 = 0;
    int count_pt2 = 0;

    while (std::getline(file, line)) {
        char side = line[0];
        int quantity = std::stoi(line.substr(1));

        while (quantity > LOCK_LENGTH) {
            quantity -= LOCK_LENGTH;
            count_pt2++;
        }

        if (side == 'L') {
            if (pos - quantity < 0 && pos != 0)
                count_pt2++;

            pos = (pos - quantity) % LOCK_LENGTH;

            if (pos < 0)
                pos += LOCK_LENGTH;
        } else {
            if (pos + quantity > LOCK_LENGTH)
                count_pt2++;

            pos = (pos + quantity) % LOCK_LENGTH;
        }

        if (pos == 0)
            count_pt1++;
    }

    std::cout << "Day1 | Part1 | C++ result: " << count_pt1 << "\n";
    std::cout << "Day1 | Part2 | C++ result: " << count_pt1 + count_pt2 << "\n";

    return 0;
}