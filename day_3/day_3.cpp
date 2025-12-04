#include <iostream>
#include <string>
#include <vector>
#include "../utils/input.h"
#include "../utils/strings.h"

int max_in(std::vector<int> vector, int& max_index, int start_index = 0, int end_index = -1) {
    int max {vector[start_index]};
    max_index = start_index;
    int end = end_index == -1 ? static_cast<int>(vector.size()) : end_index;
    for(int i {start_index + 1}; i < end; i++) {
        if (vector[i] > max) {
            max = vector[i];
            max_index = i;
        }
    }
    return max;
}

unsigned long long int max_joltage_in_bank(std::vector<int> bank, int size) {
    unsigned long long int joltage {0};
    int digit_index {-1};
    for(int i {0}; i < size; i++) {
        int digit {max_in(bank, digit_index, digit_index + 1, bank.size() - size + 1 + i)};
        joltage = joltage * 10 + digit;
    }
    return joltage;
}

unsigned long long int max_joltage(std::vector<std::vector<int>> banks, int size, bool verbose) {
    unsigned long long int joltage {0};
    for (int i {0}; i < banks.size(); i++) {
        unsigned long long int bank_joltage {max_joltage_in_bank(banks[i], size)};
        if (verbose) {
            std::cout << "Max joltage in bank " << i << " is " << bank_joltage << std::endl;
        }
        joltage += bank_joltage;
    }
    return joltage;
}

void day_3(bool verbose) {
    std::vector<std::string> lines;
    read_file("day_3/input", lines);

    std::vector<std::vector<int>> banks;
    banks.resize(lines.size());

    for (int i {0}; i < lines.size(); i++) {
        string_to_int_vector(lines[i], banks[i]);
    }
    unsigned long long int  part_1 {max_joltage(banks, 2, verbose)};
    std::cout << "Max joltage (2) is " << part_1 << std::endl;
    unsigned long long int part_2 {max_joltage(banks, 12, verbose)};
    std::cout << "Max joltage (12) is " << part_2 << std::endl;
}