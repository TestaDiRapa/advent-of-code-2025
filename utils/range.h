
#include <algorithm>
#include <vector>

template<typename T>
bool intersect(std::pair<T, T> a, std::pair<T, T> b) {
    return !(a.first > b.second || a.second < b.first);
}

/**
 * ranges needs to be sorted
 */
template<typename T>
std::vector<std::pair<T, T>> merge_overlapping_ranges(std::vector<std::pair<T, T>> ranges) {
    std::vector<std::pair<T, T>> result;
    std::pair<T, T> current {ranges[0]};
    for (size_t i {1}; i < ranges.size(); i++) {
        if (intersect(ranges[i], current)) {
            current.second = std::max(current.second, ranges[i].second);
        } else {
            result.push_back(current);
            current = ranges[i];
        }
    }
    result.push_back(current);
    return result;
}