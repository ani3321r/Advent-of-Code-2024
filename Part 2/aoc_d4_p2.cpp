#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<string> grid;
    string line;

    while (getline(cin, line)) {
        grid.push_back(line);
    }

    int count = 0;

    for (int r = 1; r < grid.size() - 1; r++) {
        for (int c = 1; c < grid[0].size() - 1; c++) {
            if (grid[r][c] != 'A') continue;

            vector<char> corners = {
                grid[r - 1][c - 1], 
                grid[r - 1][c + 1], 
                grid[r + 1][c + 1], 
                grid[r + 1][c - 1]
            };

            string cornerStr(corners.begin(), corners.end());

            if (cornerStr == "MMSS" || cornerStr == "MSSM" || cornerStr == "SSMM" || cornerStr == "SMMS") {
                count++;
            }
        }
    }

    cout << count << endl;

    return 0;
}