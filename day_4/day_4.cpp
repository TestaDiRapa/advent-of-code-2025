#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../utils/input.h"
#include "../utils/strings.h"

bool is_roll_accessible(std::vector<std::string> grid, int y, int x) {
    int rolls {0};

    int y_min {std::max(0, y-1)};
    int y_max {std::min(static_cast<int>(grid.size() - 1), y+1)};
    int x_min {std::max(0, x-1)};
    int x_max {std::min(static_cast<int>(grid[y_min].size() - 1), x+1)};
    for (int i {y_min}; i <= y_max; i++) {
        for (int j {x_min}; j <= x_max; j++) {
            rolls += (grid[i][j] == '@');
        }
    }
    return (rolls - 1) < 4;
}

std::vector<std::pair<int, int>> accessible_rolls(std::vector<std::string> grid) {
    std::vector<std::pair<int, int>> rolls_coordinates;
    for(int i {0}; i < grid.size(); i++) {
        for(int j {0}; j < grid[i].size(); j++) {
            if (grid[i][j] == '@' && is_roll_accessible(grid, i, j)) {
                std::pair<int, int> roll(i, j);
                rolls_coordinates.push_back(roll);
            }
        }
    }
    return rolls_coordinates;
}

int accessible_rolls_iterative(std::vector<std::string> grid, bool verbose) {
    int rolls_removed {0};
    int step {0};
    std::vector<std::pair<int, int>> removed;
    do {
        removed = accessible_rolls(grid);
        for (std::pair<int, int> roll : removed) {
            grid[roll.first][roll.second] = '.';
        }
        if (verbose) {
            std::cout << "Removed " << removed.size() << " rolls in step " << step << std::endl;
        }
        step++;
        rolls_removed += removed.size();
    } while(removed.size() > 0);
    return rolls_removed;
}

void day_4(bool verbose) {
    std::vector<std::string> grid;
    read_file("day_4/input", grid);

    size_t part_1 {accessible_rolls(grid).size()};
    std::cout << "The rolls with < 4 adjacent rolls are: " << part_1 << std::endl;

    int part_2 {accessible_rolls_iterative(grid, verbose)};
    std::cout << "The total number of rolls removed iteratively is: " << part_2 << std::endl;
}