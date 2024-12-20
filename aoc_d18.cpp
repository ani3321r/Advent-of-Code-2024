#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

// for different size of grid for testing we can change size here
const int GRID_SIZE = 71;
vector<vector<bool>> grid(GRID_SIZE, vector<bool>(GRID_SIZE, false));
vector<vector<bool>> visited(GRID_SIZE, vector<bool>(GRID_SIZE, false));

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

struct Point {
    int x, y, dist;
    Point(int x, int y, int dist) : x(x), y(y), dist(dist) {}
};

bool isValid(int x, int y) {
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && !grid[y][x]);
}

int bfs(int startX, int startY, int endX, int endY) {
    for(int i = 0; i < GRID_SIZE; i++) {
        fill(visited[i].begin(), visited[i].end(), false);
    }
    
    queue<Point> q;
    q.push(Point(startX, startY, 0));
    visited[startY][startX] = true;
    
    while(!q.empty()) {
        Point current = q.front();
        q.pop();
        
        if(current.x == endX && current.y == endY) {
            return current.dist;
        }
        
        for(int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            
            if(isValid(newX, newY) && !visited[newY][newX]) {
                visited[newY][newX] = true;
                q.push(Point(newX, newY, current.dist + 1));
            }
        }
    }
    
    return -1;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    int count = 0;
    
    // for different byte size we can modify here
    while(getline(cin, line) && count < 1024) {
        stringstream ss(line);
        string x_str, y_str;
        
        if(getline(ss, x_str, ',') && getline(ss, y_str)) {
            int x = stoi(x_str);
            int y = stoi(y_str);
            
            if(x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
                grid[y][x] = true;
                count++;
            }
        }
    }
    
    // also the grid size should be changed here before testing with any other examples
    int result = bfs(0, 0, 70, 70);
    
    if(result == -1) {
        cout << "No path found!" << endl;
    } else {
        cout << result << endl;
    }
    
    return 0;
}