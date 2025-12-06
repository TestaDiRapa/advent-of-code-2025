#include <string>
#include <vector>

int compare_numeric_strings(std::string a, std::string b);

std::pair<int, int> string_to_int_range(std::string_view str, char separator);

std::pair<std::string, std::string> string_to_str_range(std::string_view str, char separator);

void split_into(std::string str, char delimiter, std::vector<std::string>& dst);

void string_to_int_vector(std::string str, std::vector<int>& dst);