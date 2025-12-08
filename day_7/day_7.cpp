#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "../utils/input.h"

size_t find_tachyon_start(std::string line) {
    for(size_t i {0}; i < line.size(); i++) {
        if (line[i] == 'S') {
            return i;
        }
    }
    throw std::invalid_argument("Invalid first line: " + line);
}

int count_splits(std::vector<std::string> lines, bool verbose) {
    std::vector<std::string> output {lines};
    std::set<size_t> tachyons;
    int splits {0};
    size_t start {find_tachyon_start(lines[0])};
    tachyons.insert(start);
    for (size_t i {1}; i < lines.size(); i++) {
        std::set<size_t> tachyons_to_add;
        std::set<size_t> tachyons_to_remove;
        for (size_t t : tachyons) {
            if (lines[i][t] == '.') {
                output[i][t] = '|';
            } else if (lines[i][t] == '^') {
                splits++;
                tachyons_to_remove.insert(t);
                if (t > 0) {
                    output[i][t-1] = '|';
                    tachyons_to_add.insert(t-1);
                }
                if (t < (lines.size() - 1)) {
                    output[i][t+1] = '|';
                    tachyons_to_add.insert(t+1);
                }
            }
        }
        for(size_t t : tachyons_to_remove) {
            tachyons.erase(t);
        }
        for(size_t t : tachyons_to_add) {
            tachyons.insert(t);
        }
    }
    if (verbose) {
        for (std::string line : output) {
            std::cout << line << std::endl;
        }
    }
    return splits;
}

std::vector<std::vector<long long int>> parse_input(std::vector<std::string> lines) {
    std::vector<std::vector<long long int>> result;
    for(size_t i {0}; i < lines.size(); i++) {
        std::vector<long long int> line;
        for(size_t j {0}; j < lines[i].size(); j++) {
            if (lines[i][j] == '.') {
                line.push_back(0);
            } else if (lines[i][j] == '^') {
                line.push_back(-1);
            } else if (lines[i][j] == 'S') {
                line.push_back(1);
            }
        }
        result.push_back(line);
    }
    return result;
}

unsigned long long int count_rays(std::vector<std::string> lines, bool verbose) {
    std::vector<std::vector<long long int>> matrix {parse_input(lines)};
    for (size_t i {1}; i < matrix.size(); i++) {
        for(size_t j {0}; j < matrix[i].size(); j++) {
            if (matrix[i][j] != -1 && matrix[i-1][j] != -1) {
                matrix[i][j] = matrix[i][j] + matrix[i-1][j];
            } else if (matrix[i][j] == -1 && matrix[i-1][j] != -1) {
                if (j > 0) {
                    matrix[i][j-1] = matrix[i][j-1] + matrix[i-1][j];
                }
                if (j < (matrix[i].size() - 1)) {
                    matrix[i][j+1] = matrix[i][j+1] + matrix[i-1][j];
                }
            }
        }
    }
    if (verbose) {
        for (std::vector<long long int> line : matrix) {
            for(long long int l : line) {
                std::cout << l << '\t';
            }
            std::cout << std::endl;
        }
    }
    unsigned long long int sum {0};
    for(long long int l : matrix[matrix.size() -1]) {
        sum += l;
    }
    return sum;
}

void day_7(std::string input_file_name, bool verbose) {
    std::vector<std::string> lines;
    read_file(input_file_name, lines);

    int part_1 {count_splits(lines, verbose)};
    std::cout << "The number of splits is: " << part_1 << std::endl;
    unsigned long long int part_2 {count_rays(lines, verbose)};
    std::cout << "The number of possible rays is: " << part_2 << std::endl;
}