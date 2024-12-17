#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct coor {
    int y, x;
};

vector<vector<int>> grid;
vector<vector<int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
unordered_map<string, unordered_set<string>> pathMap;

void search(int y, int x, vector<coor>& path) {
    int curr = grid[y][x];

    if (curr == 9) {
        string firstKey = to_string(path[0].y) + "," + to_string(path[0].x);
        string lastKey = to_string(y) + "," + to_string(x);
        pathMap[firstKey].insert(lastKey);
        return;
    }

    for (auto& dir : directions) {
        int ny = y + dir[0], nx = x + dir[1];

        if (ny >= 0 && ny < grid.size() && nx >= 0 && nx < grid[0].size() && grid[ny][nx] == curr + 1) {
            path.push_back({ y, x });
            search(ny, nx, path);
            path.pop_back(); 
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    string line;
    while (cin >> line) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        grid.push_back(row);
    }

    vector<coor> path;
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[0].size(); x++) {
            if (grid[y][x] == 0) {
                path.clear();
                path.push_back({ y, x });
                search(y, x, path);
            }
        }
    }

    int sum = 0;
    for (auto& pair : pathMap) {
        sum += pair.second.size();
    }

    cout << sum << endl;

    return 0;
}