#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

struct Range {
    long long min{};
    long long max{};

    bool in_range(long long val) const { return val >= min && val <= max; }
};

std::ostream &operator<<(std::ostream &os, const Range &r) {
    return os << "R[" << r.min << ", " << r.max << "]\n";
}

template <typename T> void print_vec(const std::vector<T> &vec) {
    for (const auto &r : vec) {
        std::cout << r << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::ifstream file("day5.txt");
    std::string line;

    bool switch_to_id = false;
    std::vector<Range> ranges;
    std::vector<long long> ids;
    while (std::getline(file, line)) {
        if (line.empty()) {
            switch_to_id = true;
            continue;
        }

        if (switch_to_id) {
            ids.push_back(std::stoll(line));
        } else {
            auto separator_idx = line.find('-');
            long long min = std::stoll(line.substr(0, separator_idx));
            long long max = std::stoll(
                line.substr(separator_idx + 1, line.size() - separator_idx));

            ranges.push_back({min, max});
        }
    }

    int p1_count_fresh = 0; 
    for (long long id : ids) {
        for (const auto &r : ranges) {
            if (r.in_range(id)) {
                p1_count_fresh++;
                break;
            }
        }
    }

    std::cout << "Day 5 | Part 1 | C++ results: " << p1_count_fresh << std::endl;
    return 0;
}
