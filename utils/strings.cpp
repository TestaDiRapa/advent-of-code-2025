#include <string>
#include <vector>
#include <sstream>

void split_into(std::string str, char delimiter, std::vector<std::string>& dst) {
    std::stringstream ss(str);
    std::string buffer;

    while(getline(ss, buffer, delimiter)) {
        dst.push_back(buffer);
    }
}

void string_to_int_vector(std::string str, std::vector<int>& dst) {
    for(int i {0}; i < str.size(); i++) {
        dst.push_back(str[i] - '0');
    }
}