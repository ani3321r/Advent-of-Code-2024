#include <iostream>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <string>
#include <queue>

using namespace std;

bool loops(vector<vector<char>> &grid, int r, int c, int rows, int cols) {
    int dr = -1, dc = 0;
    unordered_set<string> seen;

    auto stateToString = [](int r, int c, int dr, int dc) {
        return to_string(r) + "," + to_string(c) + "," + to_string(dr) + "," + to_string(dc);
    };

    while (true) {
        string state = stateToString(r, c, dr, dc);
        if (seen.count(state)) return true;
        seen.insert(state);

        if (r + dr < 0 || r + dr >= rows || c + dc < 0 || c + dc >= cols) return false;

        if (grid[r + dr][c + dc] == '#') {
            int temp = dr;
            dr = dc;
            dc = -temp;
        } else {
            r += dr;
            c += dc;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<string> input;
    string line;
    while (getline(cin, line)) {
        input.push_back(line);
    }

    int rows = input.size();
    int cols = input[0].size();
    vector<vector<char>> grid(rows, vector<char>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = input[i][j];
        }
    }

    int r = 0, c = 0;
    bool found = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '^') {
                r = i;
                c = j;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    vector<pair<int, int>> emptyCells;
    for (int cr = 0; cr < rows; ++cr) {
        for (int cc = 0; cc < cols; ++cc) {
            if (grid[cr][cc] == '.') {
                emptyCells.emplace_back(cr, cc);
            }
        }
    }

    int count = 0;

    for (auto &[cr, cc] : emptyCells) {
        grid[cr][cc] = '#';
        if (loops(grid, r, c, rows, cols)) {
            ++count;
        }
        grid[cr][cc] = '.';
    }

    cout << count << endl;

    return 0;
}