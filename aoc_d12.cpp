#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

struct YX {
    int y, x;
};

vector<pair<int, int>> dirs = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

void search(int startY, int startX, char plot, vector<YX>& coords, const vector<vector<char>>& grid, vector<vector<bool>>& visited) {
    queue<YX> q;
    q.push({startY, startX});
    visited[startY][startX] = true;

    while (!q.empty()) {
        YX current = q.front();
        q.pop();
        coords.push_back(current);

        for (auto& dir : dirs) {
            int ny = current.y + dir.first;
            int nx = current.x + dir.second;

            if (ny >= 0 && ny < grid.size() && nx >= 0 && nx < grid[0].size() && !visited[ny][nx] && grid[ny][nx] == plot) {
                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }
    }
}

int perimeter(const vector<YX>& coords, const vector<vector<char>>& grid) {
    int perimeter = 0;

    for (const auto& coord : coords) {
        for (auto& dir : dirs) {
            int ny = coord.y + dir.first;
            int nx = coord.x + dir.second;

            if (ny < 0 || ny >= grid.size() || nx < 0 || nx >= grid[0].size() || grid[ny][nx] != grid[coord.y][coord.x]) {
                perimeter++;
            }
        }
    }

    return perimeter;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    vector<vector<char>> grid;
    string line;
    while (getline(cin, line)) {
        grid.push_back(vector<char>(line.begin(), line.end()));
    }

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    vector<pair<char, vector<YX>>> plots;
    int total = 0;

    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[0].size(); ++x) {
            if (!visited[y][x]) {
                vector<YX> coords;
                char plot = grid[y][x];
                search(y, x, plot, coords, grid, visited);
                total += coords.size() * perimeter(coords, grid);
            }
        }
    }

    cout << total << endl;

    return 0;
}