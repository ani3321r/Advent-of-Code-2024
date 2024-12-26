#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    string input, line;
    vector<vector<int>> locks, keys;
    vector<string> block;
    
    while (getline(cin, line)) {
        if (line.empty()) {
            vector<string> transposed(block[0].length());
            for (size_t i = 0; i < block[0].length(); i++) {
                for (size_t j = 0; j < block.size(); j++) {
                    transposed[i] += block[j][i];
                }
            }
            
            vector<int> counts;
            for (const string& row : transposed) {
                counts.push_back(count(row.begin(), row.end(), '.') - 1);
            }
            
            if (block[0][0] == '#') {
                locks.push_back(counts);
            } else {
                keys.push_back(counts);
            }
            block.clear();
        } else {
            block.push_back(line);
        }
    }
    
    if (!block.empty()) {
        vector<string> transposed(block[0].length());
        for (size_t i = 0; i < block[0].length(); i++) {
            for (size_t j = 0; j < block.size(); j++) {
                transposed[i] += block[j][i];
            }
        }
        
        vector<int> counts;
        for (const string& row : transposed) {
            counts.push_back(count(row.begin(), row.end(), '.') - 1);
        }
        
        if (block[0][0] == '#') {
            locks.push_back(counts);
        } else {
            keys.push_back(counts);
        }
    }

    int total = 0;
    for (const auto& lock : locks) {
        for (const auto& key : keys) {
            bool valid = true;
            for (size_t i = 0; i < lock.size(); i++) {
                if (lock[i] + key[i] < 5) {
                    valid = false;
                    break;
                }
            }
            if (valid) total++;
        }
    }
    
    cout << total;
    return 0;
}