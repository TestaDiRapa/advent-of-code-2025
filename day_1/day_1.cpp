#include <iostream>
#include <string>
#include <vector>
#include "../utils/input.h"

void find_pwd_using_standard_method(std::vector<std::string> lines, bool verbose) {
    short int dial_value {50};
    int count_0 {0};
    for (std::string line : lines) {
        int mult = line[0] == 'L' ? -1 : 1;
        int move = std::stoi(line.substr(1));
        dial_value += mult * (move % 100);
        if (dial_value > 99) {
            dial_value %= 100;
        } else if (dial_value < 0) {
            dial_value = 100 + dial_value;
        }
        if (verbose) {
            std::cout << "Move " << line << " - dial value: " << dial_value << std::endl;
        }
        if (dial_value == 0) {
            count_0++;
        }
    }
    std::cout << "The password is: " << count_0 << std::endl;
}

void find_pwd_using_click_method(std::vector<std::string> lines, bool verbose) {
    short int dial_value {50};
    int count_0 {0};
    for (std::string line : lines) {
        int mult = line[0] == 'L' ? -1 : 1;
        int move = std::stoi(line.substr(1));
        int dial_start = dial_value;
        dial_value += mult * (move % 100);
        if (dial_value > 99) {
            dial_value %= 100;
            count_0++;
        } else if (dial_value < 0) {
            dial_value = 100 + dial_value;
            count_0 += (dial_start != 0);
        } else if (dial_value == 0) {
            count_0++;
        }
        count_0 += (move / 100);
        if (move >= 100 && move % 100 == 0 && dial_value == 0) {
            count_0--;
        }
        if (verbose) {
            std::cout << "Move " << line << " - dial value: " << dial_value << std::endl;
        }
    }
    std::cout << "The password with the 0x434C49434B method is: " << count_0 << std::endl;
}

void day_1(bool verbose) {
    std::vector<std::string> lines;
    read_file("day_1/input", lines);
    find_pwd_using_standard_method(lines, verbose);
    find_pwd_using_click_method(lines, verbose);
}