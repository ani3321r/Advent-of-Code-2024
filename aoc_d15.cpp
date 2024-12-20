#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

vector<string> splitString(const string& str, const string& delimiter) {
    vector<string> result;
    size_t start = 0, end = 0;

    while ((end = str.find(delimiter, start)) != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }

    result.push_back(str.substr(start));
    return result;
}

vector<string> splitLines(const string& str) {
    return splitString(str, "\n");
}

pair<int, int> startPos(const vector<vector<char>>& grid) {
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[0].size(); ++x) {
            if (grid[y][x] == '@') {
                return {y, x};
            }
        }
    }
    return {-1, -1};
}

pair<int, int> dir(char token) {
    map<char, pair<int, int>> dirs = {
        {'^', {-1, 0}},
        {'>', {0, 1}},
        {'v', {1, 0}},
        {'<', {0, -1}}
    };
    return dirs[token];
}

void move(vector<vector<char>>& grid, pair<int, int>& p, const pair<int, int>& direction) {
    int ny = p.first + direction.first;
    int nx = p.second + direction.second;

    if (grid[ny][nx] == '#') return;

    if (grid[ny][nx] == '.') {
        p = {ny, nx};
        return;
    }

    if (grid[ny][nx] == 'O') {
        int dot = 0;

        try {
            for (int i = 1; i < 100; ++i) {
                int ty = ny + direction.first * i;
                int tx = nx + direction.second * i;

                if (grid[ty][tx] == '#') break;

                if (grid[ty][tx] == '.') {
                    dot = i;
                    break;
                }
            }
        } catch (...) {}

        if (dot == 0) return;

        grid[ny][nx] = '.';
        p = {ny, nx};

        for (int i = 1; i <= dot; ++i) {
            grid[ny + direction.first * i][nx + direction.second * i] = 'O';
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    string input, line;
    while (getline(cin, line)) {
        input += line + "\n";
    }

    vector<string> halves = splitString(input, "\n\n");
    vector<string> gridLines = splitLines(halves[0]);
    string movesStr = halves[1];
    movesStr.erase(remove(movesStr.begin(), movesStr.end(), '\n'), movesStr.end());

    vector<vector<char>> grid;
    for (const string& row : gridLines) {
        grid.push_back(vector<char>(row.begin(), row.end()));
    }

    pair<int, int> p = startPos(grid);
    grid[p.first][p.second] = '.';

    for (char m : movesStr) {
        pair<int, int> direction = dir(m);
        move(grid, p, direction);
    }

    int sum = 0;
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 1; x < grid[0].size(); ++x) {
            if (grid[y][x] == 'O') {
                sum += (100 * y) + x;
            }
        }
    }

    cout << sum << endl;

    return 0;
}