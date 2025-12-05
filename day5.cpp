#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

struct Range {
    long long min{};
    long long max{};

    long long range() const { return max - min + 1; }

    bool in_range(long long val) const { return val >= min && val <= max; }

    std::optional<Range> union_range(const Range &other) const {
        // Check if ranges overlap or are adjacent (touching)
        if (max < other.min - 1 || other.max < min - 1) {
            return std::nullopt; // No overlap and not adjacent
        }
        return Range{std::min(min, other.min), std::max(max, other.max)};
    }
};

std::vector<Range> collapse_ranges(std::vector<Range> ranges) {
    if (ranges.empty()) return {};

    // Sort by min value first
    std::sort(ranges.begin(), ranges.end(),
              [](const Range &a, const Range &b) { return a.min < b.min; });

    std::vector<Range> final_ranges;
    Range current = ranges[0];
    for (size_t i = 1; i < ranges.size(); ++i) {
        auto merged = current.union_range(ranges[i]);
        if (merged) {
            current = *merged;
        } else {
            final_ranges.push_back(current);
            current = ranges[i];
        }
    }
    final_ranges.push_back(current);

    return final_ranges;
}

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

    // Part 1
    int p1_count_fresh = 0;
    for (long long id : ids) {
        bool is_fresh =
            std::any_of(ranges.begin(), ranges.end(),
                        [&](const Range &r) { return r.in_range(id); });

        if (is_fresh) {
            p1_count_fresh++;
        }
    }

    // Part 2
    std::vector<Range> final_ranges = collapse_ranges(ranges);

    long long p2_count_ids = std::accumulate(
        final_ranges.begin(), final_ranges.end(), 0LL,
        [&](long long acc, const Range &r) { return acc + r.range(); });

    std::cout << "Day 5 | Part 1 | C++ results: " << p1_count_fresh
              << std::endl;

    std::cout << "Day 5 | Part 2 | C++ results: " << p2_count_ids << std::endl;
    return 0;
}
