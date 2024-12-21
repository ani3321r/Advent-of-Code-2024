#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

vector<string> readGrid();
pair<int, int> findStart(const vector<string>& grid);
vector<vector<int>> calculateDistances(const vector<string>& grid, int start_r, int start_c);
int countSpecialCells(const vector<string>& grid, const vector<vector<int>>& dists);

vector<string> readGrid() {
    vector<string> grid;
    string line;
    while (cin >> line) {
        grid.push_back(line);
    }
    return grid;
}

pair<int, int> findStart(const vector<string>& grid) {
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == 'S') return {r, c};
        }
    }
    return {-1, -1};
}

vector<vector<int>> calculateDistances(const vector<string>& grid, int start_r, int start_c) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<int>> dists(rows, vector<int>(cols, -1));
    dists[start_r][start_c] = 0;

    queue<pair<int, int>> q;
    q.push({start_r, start_c});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (auto [dr, dc] : vector<pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || grid[nr][nc] == '#' || dists[nr][nc] != -1)
                continue;

            dists[nr][nc] = dists[r][c] + 1;
            if (grid[nr][nc] == 'E') return dists;
            q.push({nr, nc});
        }
    }
    return dists;
}

int countSpecialCells(const vector<string>& grid, const vector<vector<int>>& dists) {
    int rows = grid.size(), cols = grid[0].size(), count = 0;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '#' || dists[r][c] == -1) continue;

            for (auto [dr, dc] : vector<pair<int, int>>{{2, 0}, {1, 1}, {0, 2}, {-1, 1}}) {
                int nr = r + dr, nc = c + dc;
                if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || grid[nr][nc] == '#' || dists[nr][nc] == -1)
                    continue;

                // to change the the picosecond according to the question we have to just add 2 to the asked value
                // here we are adding 2 to 100
                if (abs(dists[r][c] - dists[nr][nc]) >= 102) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<string> grid = readGrid();
    auto [start_r, start_c] = findStart(grid);
    vector<vector<int>> dists = calculateDistances(grid, start_r, start_c);
    int result = countSpecialCells(grid, dists);

    cout << result << endl;
    return 0;
}