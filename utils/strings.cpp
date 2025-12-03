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