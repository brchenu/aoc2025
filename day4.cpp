#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

constexpr int MIN_ADJACENT_THRESHOLD = 4;
constexpr char ROLL_CHAR = '@';
constexpr char REMOVED_CHAR = 'x';

int count_adjacent_rolls(const std::vector<std::vector<char>> &matrix, int row,
                         int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0)
                continue;

            const int new_row = row + i;
            const int new_col = col + j;

            if (new_row < 0 || new_row >= std::ssize(matrix))
                continue;
            if (new_col < 0 || new_col >= std::ssize(matrix[0]))
                continue;

            if (matrix[new_row][new_col] == ROLL_CHAR) {
                ++count;
            }
        }
    }
    return count;
}

bool has_few_adjacent_rolls(const std::vector<std::vector<char>> &matrix,
                            int row, int col) {
    return count_adjacent_rolls(matrix, row, col) < MIN_ADJACENT_THRESHOLD;
}

int process_rolls(std::vector<std::vector<char>> &matrix, int count) {
    std::vector<std::pair<int, int>> valid_indices;

    for (int row = 0; row < std::ssize(matrix); ++row) {
        for (int col = 0; col < std::ssize(matrix[0]); ++col) {
            if (matrix[row][col] == ROLL_CHAR &&
                has_few_adjacent_rolls(matrix, row, col)) {
                valid_indices.emplace_back(row, col);
            }
        }
    }

    for (const auto &[r, c] : valid_indices) {
        matrix[r][c] = REMOVED_CHAR;
    }

    if (valid_indices.empty()) {
        return count;
    }
    return process_rolls(matrix,
                         count + static_cast<int>(valid_indices.size()));
}

int main() {
    std::ifstream file("day4.txt");
    if (!file) {
        std::cerr << "Error while opening the file\n";
        return 1;
    }

    std::vector<std::vector<char>> matrix;
    for (std::string line; std::getline(file, line);) {
        matrix.emplace_back(line.begin(), line.end());
    }

    // Part 1
    int p1_valid_rolls = 0;
    for (int row = 0; row < std::ssize(matrix); ++row) {
        for (int col = 0; col < std::ssize(matrix[0]); ++col) {
            if (matrix[row][col] == ROLL_CHAR &&
                has_few_adjacent_rolls(matrix, row, col)) {
                ++p1_valid_rolls;
            }
        }
    }

    // Part 2
    const int p2_valid_rolls = process_rolls(matrix, 0);

    std::cout << "Day 4 | Part 1 | C++ result: " << p1_valid_rolls << '\n';
    std::cout << "Day 4 | Part 2 | C++ result: " << p2_valid_rolls << '\n';

    return 0;
}