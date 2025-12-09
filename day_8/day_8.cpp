#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "../utils/input.h"

class JunctionBox {
    public:
        long long int x;
        long long int y;
        long long int z;

        unsigned long long int distance_from(const JunctionBox& other) {
            return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z);
        }

        bool operator<(const JunctionBox& other) const {
            if (x != other.x) {
                return x < other.x;
            } else if (y != other.y) {
                return y < other.y;
            } else {
                return z < other.z;
            }
        }
};

class JunctionDistance {
    public:
        JunctionBox a;
        JunctionBox b;
        unsigned long long int d;
};

class Circuit {
    public:
        std::set<JunctionBox> boxes;

        void join_with(const Circuit& other) {
            for(JunctionBox b : other.boxes) {
                boxes.insert(b);
            }
        }

        void print_circuit() {
            std::cout << "Circuit: ";
            for(JunctionBox b : boxes) {
                std::cout << "(" << b.x << "," << b.y << "," << b.z << "), ";
            }
            std::cout << std::endl;
        }
};

bool compare_junction_distances(JunctionDistance a, JunctionDistance b) {
    return a.d < b.d;
}

bool compare_circuits(Circuit a, Circuit b) {
    return b.boxes.size() < a.boxes.size();
}

std::vector<JunctionDistance> compute_distances(std::vector<JunctionBox> junctions) {
    std::vector<JunctionDistance> result;
    for(size_t i {0}; i < (junctions.size() -1); i++) {
        for(size_t j {i+1}; j < (junctions.size()); j++) {
            JunctionBox a {junctions[i]};
            JunctionBox b {junctions[j]};
            result.push_back({a, b, a.distance_from(b) }); 
        }
    }
    std::sort(result.begin(), result.end(), compare_junction_distances);
    return result;
}

std::vector<Circuit> assemble_x_nearest_circuits(std::vector<JunctionDistance> junctions, size_t x, bool verbose) {
    std::vector<Circuit> result;
    for(size_t i {0}; i < x; i++) {
        JunctionDistance test {junctions[i]};
        if (verbose) {
            std::cout << "Pass: " << i << std::endl;
            std::cout << "Testing :";
            std::cout << "(" << test.a.x << "," << test.a.y << "," << test.a.z << ") - ";
            std::cout << "(" << test.b.x << "," << test.b.y << "," << test.b.z << ")" << std::endl;
        }
        std::set<size_t> matches;
        for(size_t j {0}; j < result.size(); j++) {
            if (result[j].boxes.contains(test.a) || result[j].boxes.contains(test.b)) {
                matches.insert(j);
            }
        }
        if (matches.size() == 0) {
            if (verbose) {
                std::cout << "No matches, adding" << std::endl;
            }
            result.push_back({ {test.a, test.b} });
        } else {
            std::vector<Circuit> tmp;
            Circuit acc({test.a, test.b});
            for(size_t j {0}; j < result.size(); j++) {
                if(matches.contains(j)) {
                    if (verbose) {
                        std::cout << "Matched: ";
                        result[j].print_circuit();
                    }
                    acc.join_with(result[j]);
                } else {
                    tmp.push_back(result[j]);
                }
            }
            tmp.push_back(acc);
            result = tmp;
            if (verbose) {
                std::cout << "Final circuit: ";
                acc.print_circuit();
            }
        }
        if (verbose) {
            for (Circuit c : result) {
                c.print_circuit();
            }
            std::cout << std::endl;
        }
    }
    std::sort(result.begin(), result.end(), compare_circuits);
    return result;
}

unsigned long long int compute_result(std::vector<Circuit> circuits, size_t count) {
    unsigned long long int product {1};
    for (size_t i {0}; i < count; i++) {
        product *= circuits[i].boxes.size();
    }
    return product;
}

JunctionDistance find_last_junction(std::vector<JunctionDistance> junctions, unsigned int total_junctions) {
    std::vector<Circuit> result;
    JunctionDistance last_junction;
    size_t i {0};
    std::cout << "---" << std::endl;
    do {
        last_junction = junctions[i];
        std::cout << "(" << last_junction.a.x << "," << last_junction.a.y << "," << last_junction.a.z << ") - ";
        std::cout << "(" << last_junction.b.x << "," << last_junction.b.y << "," << last_junction.b.z << ") " << std::endl;
        std::set<size_t> matches;
        for(size_t j {0}; j < result.size(); j++) {
            if (result[j].boxes.contains(last_junction.a) || result[j].boxes.contains(last_junction.b)) {
                matches.insert(j);
            }
        }
        if (matches.size() == 0) {
            result.push_back({ {last_junction.a, last_junction.b} });
        } else {
            std::vector<Circuit> tmp;
            Circuit acc({last_junction.a, last_junction.b});
            for(size_t j {0}; j < result.size(); j++) {
                if(matches.contains(j)) {
                    acc.join_with(result[j]);
                } else {
                    tmp.push_back(result[j]);
                }
            }
            tmp.push_back(acc);
            result = tmp;
        }
        i++;
    } while(result.size() > 1 || result[0].boxes.size() < total_junctions);
    return last_junction;
}

void day_8(std::string input_file_name, bool verbose) {
    std::vector<JunctionBox> junctions {read_input<JunctionBox>(input_file_name, [](const std::string& s) {
        std::vector<long long int> coordinates {split_convert<long long int>(s, ",", [](const std::string& s) { return std::stoll(s);})};
        return JunctionBox{ coordinates[0], coordinates[1], coordinates[2] };
    })};

    std::vector<JunctionDistance> distances{compute_distances(junctions)};

    if (verbose) {
        for (JunctionDistance d : distances) {
            std::cout << "(" << d.a.x << "," << d.a.y << "," << d.a.z << ") - ";
            std::cout << "(" << d.b.x << "," << d.b.y << "," << d.b.z << "): " << d.d << std::endl;
        }
    }

    std::vector<Circuit> circuits {assemble_x_nearest_circuits(distances, 1000, verbose)};
    if (verbose) {
        for (Circuit c : circuits) {
            c.print_circuit();
        }
    }

    unsigned long long int part_1 {compute_result(circuits, 3)};
    std::cout << "The product of the size of the 3 largest circuits is: " << part_1 << std::endl;
    JunctionDistance part_2 {find_last_junction(distances, junctions.size())};
    if (verbose) {
        std::cout << "The last junction is: ";
        std::cout << "(" << part_2.a.x << "," << part_2.a.y << "," << part_2.a.z << ") - ";
        std::cout << "(" << part_2.b.x << "," << part_2.b.y << "," << part_2.b.z << ") " << std::endl;
    }
    std::cout << "The product of the x of the last 2 junctions to be connected is: " << (part_2.a.x * part_2.b.x) << std::endl;
}