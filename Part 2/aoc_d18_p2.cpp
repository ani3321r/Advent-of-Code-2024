#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <sstream>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

bool hasPath(vector<vector<bool>> &grid, int n, int m) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<pair<int, int>> q;

    if (!grid[0][0]) return false;
    q.push({0, 0});
    visited[0][0] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == n - 1 && y == m - 1) return true;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < n && ny < m && !visited[nx][ny] && grid[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    return false;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int n = 71, m = 71;
    vector<vector<bool>> grid(n, vector<bool>(m, true));
    vector<pair<int, int>> nodes;

    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        int x, y;
        char comma;
        ss >> x >> comma >> y;
        nodes.push_back({x, y});
    }

    for (auto &[x, y] : nodes) {
        grid[x][y] = false;
        if (!hasPath(grid, n, m)) {
            cout << x << "," << y << endl;
            break;
        }
    }

    return 0;
}