#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../utils/input.h"
#include "../utils/strings.h"
#include "../utils/range.h"

bool compare_ranges(std::pair<std::string, std::string> a, std::pair<std::string, std::string> b) {
    return compare_numeric_strings(a.first, b.first) < 0;
}

bool is_in_range(std::pair<std::string, std::string> range, std::string test) {
    return (compare_numeric_strings(test, range.first) >= 0) && (compare_numeric_strings(test, range.second) <= 0);
}

int count_fresh_ingredients(std::vector<std::pair<std::string, std::string>> fresh_ingredients, std::vector<std::string> available_ingredients, bool verbose) {
    int count {0};
    for(std::string ingredient : available_ingredients) {
       for(std::pair<std::string, std::string> range : fresh_ingredients) {
            if (is_in_range(range, ingredient)) {
                if (verbose) {
                    std::cout << ingredient << " is fresh" << std::endl;
                }
                count++;
                break;
            }
       }
    }
    return count;
}

unsigned long long int count_all_possible_fresh_ingredients(std::vector<std::pair<std::string, std::string>> fresh_ingredients) {
    unsigned long long int count {0};
    std::vector<std::pair<unsigned long long int,  unsigned long long int>> fresh_ingredients_ulli;

    for(std::pair<std::string, std::string> range : fresh_ingredients) {
        fresh_ingredients_ulli.push_back({
            std::stoull(range.first),
            std::stoull(range.second)
        });
    }

    std::vector<std::pair<unsigned long long int,  unsigned long long int>> merged_fresh_ingredients {merge_overlapping_ranges(fresh_ingredients_ulli)};
    
    for(std::pair<unsigned long long int, unsigned long long int> range : merged_fresh_ingredients) {
        count += (range.second - range.first) + 1;
    }
    return count;
}

void day_5(std::string input_file_name, bool verbose) {
    std::vector<std::string> lines;
    read_file(input_file_name, lines);

    std::vector<std::pair<std::string, std::string>> fresh_ingredients;
    std::vector<std::string> available_ingredients;
    for(std::string line : lines) {
        if (verbose) {
            std::cout << line << std::endl;
        }
        if (line.find('-') != std::string::npos) {
            fresh_ingredients.push_back(string_to_str_range(line, '-'));
        } else if (line.size() > 0) {
            available_ingredients.push_back(line);
        }
    }

    std::sort(fresh_ingredients.begin(), fresh_ingredients.end(), compare_ranges);

    int part_1 {count_fresh_ingredients(fresh_ingredients, available_ingredients, verbose)};
    std::cout << "The number of fresh ingredients is: " << part_1 << std::endl;
    unsigned long long int part_2 {count_all_possible_fresh_ingredients(fresh_ingredients)};
    std::cout << "The number of possible fresh ingredients is: " << part_2 << std::endl;
}