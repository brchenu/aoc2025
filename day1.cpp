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
    int count = 0;
    while (std::getline(file, line)) {
        char side = line[0];
        int quantity = std::stoi(line.substr(1));

        if (side == 'L') {
            pos = (pos - quantity) % 100;
            if (pos < 0)
                pos += 100;
        } else {
            pos = (pos + quantity) % 100;
        }

        if (pos == 0)
            count++;
    }

    std::cout << "Day1 | Part1 | C++ result: " << count << "\n";

    return 0;
}