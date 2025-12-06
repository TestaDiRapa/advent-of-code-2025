#include <iostream>
#include <string>
#include <vector>
#include "../utils/input.h"
#include "../utils/strings.h"

void divisors_of(int n, std::vector<int>& dst) {
    dst.push_back(1);
    for(int i {2}; i <= n/2; i++) {
        if (n % i == 0) {
            dst.push_back(i);
        }
    }
}

int get_magnitude(unsigned long long int n) {
    int m {1};
    unsigned long long int divisor {10};
    while (n / divisor > 0) {
        m++;
        divisor *= 10;
    }
    return m;
}

unsigned long long int pow_10(int exp) {
    if (exp == 0) {
        return 1;
    } else {
        unsigned long long int res = {10};
        for(int i{1}; i < exp; i++) {
            res *= 10;
        }
        return res;
    }
}

bool check_repeated_segment(unsigned long long int id, int segment_size) {
    unsigned long long int mask {pow_10(segment_size)};
    unsigned long long int segment {id % mask};
    while(id > 0) {
        if ((id % mask) != segment) {
            return false;
        }
        id = id / mask;
    }
    return true;
}

bool is_invalid_id(unsigned long long int id) {
    int magnitude = get_magnitude(id);
    if (magnitude % 2 != 0) {
        return false;
    }
    unsigned long long int mask {pow_10(magnitude/2)};
    return (id % mask) == (id/mask);
}

bool is_invalid_id_repeated(unsigned long long int id, std::vector<int>* cached_divisors) {
    int magnitude = get_magnitude(id);
    std::vector<int> divisors = cached_divisors[magnitude-1];
    for(int divisor : divisors) {
        if (check_repeated_segment(id, divisor)) {
            return true;
        }
    }
    return false;
}


unsigned long long int sum_invalid_ids(unsigned long long int from, unsigned long long int to, bool verbose) {
    unsigned long long int invalid_ids_sum {0};
    for(unsigned long long int id {from}; id <= to; id++) {
        if (id > 10 && is_invalid_id(id)) {
            invalid_ids_sum += id;
            if (verbose) {
                std::cout << id << " is invalid" << std::endl;
            }
        }
    }
    return invalid_ids_sum;
}

unsigned long long int sum_invalid_ids_repeated(unsigned long long int from, unsigned long long int to, std::vector<int>* cached_divisors, bool verbose) {
    unsigned long long int invalid_ids_sum {0};
    for(unsigned long long int id {from}; id <= to; id++) {
        if (id > 10 && is_invalid_id_repeated(id, cached_divisors)) {
            invalid_ids_sum += id;
            if (verbose) {
                std::cout << id << " is invalid" << std::endl;
            }
        }
    }
    return invalid_ids_sum;
}

void day_2(std::string input_file_name, bool verbose) {
    std::vector<std::string> lines;
    read_file(input_file_name, lines);

    std::vector<std::string> bounds;
    split_into(lines[0], ',', bounds);

    std::vector<int>* cached_divisors = new std::vector<int>[20];
    for(int i {0}; i < 20; i++) {
        divisors_of(i+1, cached_divisors[i]);
    }

    unsigned long long int sum_part_1 {0};
    unsigned long long int sum_part_2 {0};

    for(size_t i {0}; i < bounds.size(); i++) {
        std::vector<std::string> buffer;
        split_into(bounds[i], '-', buffer);
        unsigned long long int lower_bound = std::stoull(buffer[0]);
        unsigned long long int upper_bound = std::stoull(buffer[1]);
       // sum_part_1 += sum_invalid_ids(lower_bound, upper_bound, verbose);
        sum_part_2 += sum_invalid_ids_repeated(lower_bound, upper_bound, cached_divisors, verbose);
    }
    std::cout << "The sum of all the invalid ids is: " << sum_part_1 << std::endl;
    std::cout << "The sum of all the invalid ids consindering multiple repetitions is: " << sum_part_2 << std::endl;
}