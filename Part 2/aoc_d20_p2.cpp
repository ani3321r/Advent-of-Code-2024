#include <iostream> 
#include <vector>
#include <queue>
#include <map>
#include <cmath>
using namespace std;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    Point start;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'S') {
                start = Point(i, j);
                break;
            }
        }
    }

    map<Point, int> dist;
    queue<Point> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];
            Point next(newX, newY);

            if (isValid(newX, newY, rows, cols) && 
                grid[newX][newY] != '#' && 
                dist.find(next) == dist.end()) {
                dist[next] = dist[curr] + 1;
                q.push(next);
            }
        }
    }

    int cheat_dist = 20;
    int result = 0;

    vector<pair<Point, int>> points;
    for (const auto& p : dist) {
        points.push_back(p);
    }

    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < points.size(); j++) {
            if (i == j) continue;
            
            int manhattan_dist = abs(points[i].first.x - points[j].first.x) + 
                               abs(points[i].first.y - points[j].first.y);
            
            if (manhattan_dist <= cheat_dist && 
                points[j].second - points[i].second - manhattan_dist >= 100) {
                result++;
            }
        }
    }

    cout << result;
    return 0;
}