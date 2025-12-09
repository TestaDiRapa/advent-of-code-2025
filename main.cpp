#include <iostream>
#include "day_1/day_1.h"
#include "day_2/day_2.h"
#include "day_3/day_3.h"
#include "day_4/day_4.h"
#include "day_5/day_5.h"
#include "day_6/day_6.h"
#include "day_7/day_7.h"
#include "day_8/day_8.h"

int main(int argc, char* argv[]) {
    bool verbose {false};
    int day;
    std::string input_file_name {argv[1]};
    if (argc >= 3) {
        std::string arg = argv[2];
        verbose = arg == "true";
    } 

    std::cout << "Day to execute: ";
    std::cin >> day;
    switch(day) {
        case 1:
            day_1(input_file_name, verbose);
            break;
        case 2:
            day_2(input_file_name, verbose);
            break;
        case 3:
            day_3(input_file_name, verbose);
            break;
        case 4:
            day_4(input_file_name, verbose);
            break;
        case 5:
            day_5(input_file_name, verbose);
            break;
        case 6:
            day_6(input_file_name, verbose);
            break;
        case 7:
            day_7(input_file_name, verbose);
            break;
        case 8:
            day_8(input_file_name, verbose);
            break;
        default:
            std::cout << "Day " << day << " not solved yet or invalid" << std::endl;
    }
    return 0;
}
