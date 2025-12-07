#include <iostream>
#include <string>
#include <vector>
#include "../utils/input.h"
#include "../utils/strings.h"

unsigned long int reduce(std::vector<int> operands, unsigned long int acc, const std::function<unsigned long int(unsigned long int, int)>& op) {
    unsigned long int total {acc};
    for(int operand : operands) {
        total = op(total, operand);
    }
    return total;
}

void print_operation(std::vector<int> operands, char op) {
    std::cout << "Operation: ";
    for(int num : operands) {
        std::cout << num << " " << op << " ";
    }
    std::cout << std::endl;
}

unsigned long int do_math(std::vector<std::vector<int>> operands, std::vector<char> operators, bool verbose) {
    unsigned long int sum {0};
    for(size_t i {0}; i < operators.size(); i++) {
        if (verbose) {
            print_operation(operands[i], operators[i]);
        }
        switch(operators[i]) {
            case '+':
                sum += reduce(operands[i], 0, [](unsigned long int sum, int it) { return sum + it; });
                break;
            case '*':
                sum += reduce(operands[i], 1, [](unsigned long int sum, int it) { return sum * it; });
                break;
            default:
                std::cout << "Invalid operator: " << operators[i] << std::endl;
        }
    }
    return sum;
}

std::vector<std::vector<int>> read_tab_input(std::vector<std::string> lines) {
    std::vector<std::vector<int>> result;
    std::string operator_line {lines[lines.size() - 1]};
    size_t start_tab {0};
    size_t i {1};
    do {
        std::vector<int> tmp;
        while(i < operator_line.size() && operator_line[i] == ' ') {
            i++;
        }
        for(size_t j {start_tab}; j < i; j++) {
            int acc {0};
            for(size_t k {0}; k < lines.size(); k++) {
                if (std::isdigit(lines[k][j])) {
                    acc = (acc * 10) + (lines[k][j] - '0');
                }
            }
            if (acc != 0) {
                tmp.push_back(acc);
            }   
        }
        result.push_back(tmp);
        start_tab = i;
        i++;
    } while(i < operator_line.size());
    return result;
}

void day_6(std::string input_file_name, bool verbose) {
    std::vector<std::string> lines;
    read_file(input_file_name, lines);

    std::vector<std::vector<int>> operands_by_line;
    std::vector<char> operators;

    for(size_t i {0}; i < lines.size(); i++) {
        if (i == (lines.size() - 1)) {
            operators = split_convert<char>(lines[i], "\\s+", [](const std::string& s) { return s[0];});
        } else {
            operands_by_line.push_back(
                split_convert<int>(lines[i], "\\s+", [](const std::string& s) { return std::stoi(s);})
            );
        }
    }

    std::vector<std::vector<int>> operands;
    for(size_t i {0}; i < operators.size(); i++) {
        std::vector<int> tmp;
        for(size_t j {0}; j < operands_by_line.size(); j++) {
            tmp.push_back(operands_by_line[j][i]);
        }
        operands.push_back(tmp);
    }
    
    unsigned long int part_1 {do_math(operands, operators, verbose)};
    std::cout << "The grand total is: " << part_1 << std::endl;

    // Part 2

    std::vector<std::vector<int>> remapped_operands {read_tab_input(lines)};

    /**
    for(std::vector<int> op : remapped_operands) {
        for(int o : op) {
            std::cout << o << " ";
        }
        std::cout << std::endl;
    }
        **/
    unsigned long int part_2 {do_math(remapped_operands, operators, verbose)};
    std::cout << "The grand total in squid math is: " << part_2 << std::endl;
}