#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

using Grid = vector<vector<char>>;
using Coordinate = pair<int, int>;
using AntennasMap = unordered_map<char, vector<Coordinate>>;

void populateAntennas(const Grid& grid, AntennasMap& antennas) {
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            char antenna = grid[y][x];
            if (antenna == '.') continue;

            if (!antennas.count(antenna)) {
                antennas[antenna] = {};
            }
            antennas[antenna].push_back({y, x});
        }
    }
}

Grid initializeAntinodes(int rows, int cols) {
    return Grid(rows, vector<char>(cols, '.'));
}

void markAntinodes(const AntennasMap& antennas, Grid& antinodes) {
    for (const auto& antenna : antennas) {
        const auto& coords = antenna.second;

        for (size_t i = 0; i < coords.size(); i++) {
            for (size_t j = 0; j < coords.size(); j++) {
                if (i == j) continue;

                int dy = coords[i].first - coords[j].first;
                int dx = coords[i].second - coords[j].second;

                int ny = coords[i].first + dy;
                int nx = coords[i].second + dx;

                if (ny >= 0 && ny < antinodes.size() && nx >= 0 && nx < antinodes[0].size()) {
                    antinodes[ny][nx] = '#';
                }
            }
        }
    }
}

int countAntinodes(const Grid& antinodes) {
    int sum = 0;
    for (const auto& row : antinodes) {
        for (char cell : row) {
            if (cell == '#') {
                sum++;
            }
        }
    }
    return sum;
}

int main() {
    #ifndef ONLINE_JUDGE  
    freopen("input.txt", "r", stdin);  
    freopen("output.txt", "w", stdout);
    #endif 
    
    Grid grid;
    string curr_line;
    while(getline(cin,  curr_line)) {
        grid.push_back(vector<char>(curr_line.begin(), curr_line.end()));
    }

    AntennasMap antennas;
    populateAntennas(grid, antennas);
    Grid antinodes = initializeAntinodes(grid.size(), grid[0].size());
    markAntinodes(antennas, antinodes);
    int sum = countAntinodes(antinodes);

    cout << "Sum of antinodes: " << sum << endl;
    
    return 0;
}