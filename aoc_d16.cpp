#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct State {
    pair<int, int> pos;
    pair<int, int> dir;
    int turns;
    int length;

    int cost() const {
        return turns * 1000 + length;
    }

    bool operator>(const State &other) const {
        return cost() > other.cost();
    }
};

vector<string> grid;

bool isValid(int y, int x, int rows, int cols) {
    return (y >= 0 && y < rows && x >= 0 && x < cols && grid[y][x] != '#');
}

int search(int startY, int startX, int endY, int endX) {
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    priority_queue<State, vector<State>, greater<State>> pq;
    map<tuple<int, int, int>, int> visited;

    pq.push({{startY, startX}, {-1, -1}, 0, 0});

    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        int y = curr.pos.first;
        int x = curr.pos.second;

        if (y == endY && x == endX) {
            return curr.cost();
        }

        int dirIndex = (curr.dir.first == -1 && curr.dir.second == -1)
                           ? -1
                           : find(directions.begin(), directions.end(), curr.dir) - directions.begin();
        auto vk = make_tuple(y, x, dirIndex);

        if (visited.count(vk) && visited[vk] <= curr.cost()) continue;
        visited[vk] = curr.cost();

        for (const auto &dir : directions) {
            int ny = y + dir.first;
            int nx = x + dir.second;

            if (!isValid(ny, nx, grid.size(), grid[0].size())) continue;

            State next = {{ny, nx}, dir, curr.turns, curr.length + 1};

            if (curr.dir != make_pair(-1, -1) && curr.dir != dir) {
                next.turns++;
            }

            pq.push(next);
        }
    }

    return -1;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    string line;
    while (getline(cin, line)) {
        grid.push_back(line);
    }

    int startY = grid.size() - 2;
    int startX = 1;
    int endY = 1;
    int endX = grid[0].size() - 2;

    int result = search(startY, startX, endY, endX);
    cout << result << endl;

    return 0;
}