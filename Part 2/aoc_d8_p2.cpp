#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<string> grid;
    string line;

    while (cin >> line) {
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    map<char, vector<pair<int, int>>> antennas;
    set<pair<int, int>> antinodes;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            char ch = grid[r][c];
            if (ch != '.') {
                antennas[ch].push_back({r, c});
            }
        }
    }

    for (const auto& array : antennas) {
        const auto& positions = array.second;
        for (size_t i = 0; i < positions.size(); i++) {
            for (size_t j = 0; j < positions.size(); j++) {
                if (i == j) continue;

                int r1 = positions[i].first;
                int c1 = positions[i].second;
                int r2 = positions[j].first;
                int c2 = positions[j].second;

                int dr = r2 - r1;
                int dc = c2 - c1;

                int r = r1, c = c1;
                while (r >= 0 && r < rows && c >= 0 && c < cols) {
                    antinodes.insert({r, c});
                    r += dr;
                    c += dc;
                }
            }
        }
    }

    int count = 0;
    for (const auto& node : antinodes) {
        int r = node.first;
        int c = node.second;
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}