#include <iostream>
#include <string>
#include <vector>

class GridDirections {
private:
    const std::vector<std::vector<char>>& grid;

public:
    GridDirections(const std::vector<std::vector<char>>& input_grid) : grid(input_grid) {}

    std::string right(int i, int j) const {
        return boundedSubstring(i, j, 0, 1, 4);
    }

    // std::string left(int i, int j) const {
    //     return boundedSubstring(i, j, 0, -1, 4);
    // }

    // std::string down(int i, int j) const {
    //     return boundedSubstring(i, j, 1, 0, 4);
    // }

    std::string up(int i, int j) const {
        return boundedSubstring(i, j, -1, 0, 4);
    }

    // std::string diagonalDownRight(int i, int j) const {
    //     return boundedSubstring(i, j, 1, 1, 4);
    // }

    std::string diagonalDownLeft(int i, int j) const {
        return boundedSubstring(i, j, 1, -1, 4);
    }

    // std::string diagonalUpRight(int i, int j) const {
    //     return boundedSubstring(i, j, -1, 1, 4);
    // }

    std::string diagonalUpLeft(int i, int j) const {
        return boundedSubstring(i, j, -1, -1, 4);
    }

private:
    std::string boundedSubstring(int i, int j, int row_delta, int col_delta, int length) const {
        std::string result;

        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[i].size()) {
            return result;
        }

        for (int k = 0; k < length; ++k) {
            int new_i = i + k * row_delta;
            int new_j = j + k * col_delta;

            if (new_i < 0 || new_i >= grid.size() || 
                new_j < 0 || new_j >= grid[new_i].size()) {
                return result;
            }

            result += grid[new_i][new_j];
        }

        return result;
    }
};

int main(){

    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin); 
    freopen("output.txt","w",stdout);
    #endif


    std::vector<std::vector<char>> grid;
    std::string current_line;

    while (std::getline(std::cin, current_line)) {
        grid.push_back(std::vector<char>(current_line.begin(), current_line.end()));
    }

    // std::cout << grid[0][0];
    GridDirections dir(grid);

    int xmasses = 0;

    for (size_t it1 = 0; it1 < grid.size(); ++it1) {
        for (size_t it2 = 0; it2 < grid[it1].size(); ++it2) {
            if(dir.right(it1,it2) == "XMAS") xmasses++;
            if(dir.right(it1,it2) == "SAMX") xmasses++;
            if(dir.up(it1,it2) == "XMAS") xmasses++;
            if(dir.up(it1,it2) == "SAMX") xmasses++;
            if(dir.diagonalDownLeft(it1,it2) == "SAMX") xmasses++;
            if(dir.diagonalDownLeft(it1,it2) == "XMAS") xmasses++;
            if(dir.diagonalUpLeft(it1,it2) == "SAMX") xmasses++;
            if(dir.diagonalUpLeft(it1,it2) == "XMAS") xmasses++;
        }
    }
    std::cout << xmasses;
}