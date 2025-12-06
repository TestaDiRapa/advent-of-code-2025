#include <string>
#include <vector>
#include <sstream>

int compare_numeric_strings(std::string a, std::string b) {
    if (a.size() < b.size()) {
        return -1;
    } else if (a.size() > b.size()) {
        return 1;
    } else {
        return a.compare(b);
    }
}


std::pair<int, int> string_to_int_range(std::string_view str, char separator) {
    size_t pos = str.find(separator);
    
    if (pos == std::string_view::npos) {
        throw std::invalid_argument("Separator not found");
    }

    return {
        std::stoi(std::string(str.substr(0, pos))),
        std::stoi(std::string(str.substr(pos + 1)))
    };
}

std::pair<std::string, std::string> string_to_str_range(std::string_view str, char separator) {
    size_t pos = str.find(separator);
    
    if (pos == std::string_view::npos) {
        throw std::invalid_argument("Separator not found");
    }
    
    return {
        std::string(str.substr(0, pos)),
        std::string(str.substr(pos + 1))
    };
}

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