#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void read_file(std::string file_name, std::vector<std::string>& lines_buffer) {
    std::string line;
    std::ifstream input_file (file_name);
    if (input_file.is_open()) {
        while (getline(input_file, line)){ 
            lines_buffer.push_back(line);
        }
        input_file.close();
    } else {
        std::cout << "Unable to open file " << file_name << std::endl;
    }
}