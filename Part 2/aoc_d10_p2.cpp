#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>

using namespace std;

int score(const vector<vector<int>> &grid, int r, int c) {
    int rows = grid.size();
    int cols = grid[0].size();

    queue<pair<int, int>> q;
    map<pair<int, int>, int> seen;

    q.push({r, c});
    seen[{r, c}] = 1;
    int trails = 0;

    while (!q.empty()) {
        auto [cr, cc] = q.front();
        q.pop();

        if (grid[cr][cc] == 9) {
            trails += seen[{cr, cc}];
        }

        vector<pair<int, int>> neighbors = {{cr - 1, cc}, {cr, cc + 1}, {cr + 1, cc}, {cr, cc - 1}};
        for (auto [nr, nc] : neighbors) {
            if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
            if (grid[nr][nc] != grid[cr][cc] + 1) continue;

            if (seen.find({nr, nc}) != seen.end()) {
                seen[{nr, nc}] += seen[{cr, cc}];
                continue;
            }

            seen[{nr, nc}] = seen[{cr, cc}];
            q.push({nr, nc});
        }
    }

    return trails;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<vector<int>> grid;
    string line;

    while (getline(cin, line)) {
        vector<int> row;
        for (char ch : line) {
            row.push_back(ch - '0');
        }
        grid.push_back(row);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    vector<pair<int, int>> trailheads;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 0) {
                trailheads.push_back({r, c});
            }
        }
    }

    int totalScore = 0;
    for (auto [r, c] : trailheads) {
        totalScore += score(grid, r, c);
    }

    cout << totalScore;

    return 0;
}