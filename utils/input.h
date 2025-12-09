#include <regex>
#include <string>
#include <vector>

void read_file(std::string file_name, std::vector<std::string>& lines);

template<typename T>
std::vector<T> split_convert(std::string s, std::string regex, std::function<T(const std::string&)> converter) {
    std::vector<T> result;
    std::regex separator(regex);
    std::sregex_token_iterator iter(s.begin(), s.end(), separator, -1);
    std::sregex_token_iterator end;
    while(iter != end) {
        std::string token = *iter;
        if(token.size() > 0) {
            result.push_back(converter(token));
        }
        iter++;
    }
    return result;
}

template<typename T>
std::vector<T> read_input(std::string file_name, std::function<T(const std::string&)> converter) {
    std::vector<T> result;
    std::vector<std::string> buffer;
    read_file(file_name, buffer);
    for(std::string line : buffer) {
        result.push_back(converter(line));
    }
    return result;
}