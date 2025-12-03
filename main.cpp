#include <iostream>
#include "day_1/day_1.h"
#include "day_2/day_2.h"

int main(int argc, char* argv[]){
    bool verbose {false};
    int day;

    if (argc >= 2) {
        std::string arg = argv[1];
        verbose = arg == "true";
    } 

    std::cout << "Day to execute: ";
    std::cin >> day;
    switch(day) {
        case 1:
            day_1(verbose);
            break;
        case 2:
            day_2(verbose);
            break;
        default:
            std::cout << "Day " << day << " not solved yet" << std::endl;
    }
    return 0;
}
