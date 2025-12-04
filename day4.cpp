#include <fstream>
#include <iostream>
#include <vector>

bool count_adjacent_rolls(const std::vector<std::vector<char>> &matrix, int row,
                          int col) {
    int count = 0;
    for (int i = -1; i < 2; i++) {
        if (row + i < 0 || row + i >= matrix.size())
            continue;
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0)
                continue;
            if (col + j < 0 || col + j >= matrix[0].size())
                continue;
            if (matrix[row + i][col + j] == '@')
                count++;
        }
    }

    return count < 4;
}

int process_rolls(std::vector<std::vector<char>> &matrix, int count) {
    std::vector<std::pair<int, int>> valid_indices;
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[0].size(); col++) {
            if (matrix[row][col] == '@') {
                if (count_adjacent_rolls(matrix, row, col)) {
                    valid_indices.emplace_back(row, col);
                }
            }
        }
    }

    for (const auto &[row, col] : valid_indices) {
        matrix[row][col] = 'x';
    }

    if(valid_indices.empty()) {
        return count;
    } else {
        return process_rolls(matrix, count + valid_indices.size());
    }
}

int main() {
    std::ifstream file("day4.txt");
    if (!file) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> matrix;

    std::string line;
    while (std::getline(file, line)) {
        matrix.emplace_back(line.begin(), line.end());
    }

    // Part 1
    int p1_valid_rolls = 0;
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[0].size(); col++) {
            if (matrix[row][col] == '@') {
                if (count_adjacent_rolls(matrix, row, col)) {
                    p1_valid_rolls++;
                }
            }
        }
    }

    // Part 2
    int p2_valid_rolls = process_rolls(matrix, 0);

    std::cout << "Day 4 | Part 1 | C++ result: " << p1_valid_rolls << std::endl;
    std::cout << "Day 4 | Part 2 | C++ result: " << p2_valid_rolls << std::endl;
}