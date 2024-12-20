#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <unordered_map>
using namespace std;

unordered_map<string_view, bool> memo;

bool isPossible(string_view design, const vector<string>& towels) {
    if (design.empty()) {
        return true;
    }

    if (memo.count(design)) {
        return memo[design];
    }

    for (const string& towel : towels) {
        if (design.length() >= towel.length() && 
            design.substr(0, towel.length()) == towel) {
            if (isPossible(design.substr(towel.length()), towels)) {
                memo[design] = true;
                return true;
            }
        }
    }
    memo[design] = false;
    return false;
}

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    tokens.reserve(100);
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != string::npos) {
        string token = str.substr(start, end - start);
        while (!token.empty() && isspace(token.front())) token.erase(0, 1);
        while (!token.empty() && isspace(token.back())) token.pop_back();
        if (!token.empty()) tokens.push_back(token);
        start = end + 1;
        end = str.find(delimiter, start);
    }
    
    string token = str.substr(start);
    while (!token.empty() && isspace(token.front())) token.erase(0, 1);
    while (!token.empty() && isspace(token.back())) token.pop_back();
    if (!token.empty()) tokens.push_back(token);
    
    return tokens;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    string towelsLine;
    if (!getline(cin, towelsLine)) {
        cout << "0\n";
        return 0;
    }
    vector<string> towels = split(towelsLine, ',');

    string emptyLine;
    getline(cin, emptyLine);

    string design;
    int possibleCount = 0;
    
    while (getline(cin, design)) {
        if (!design.empty()) {
            while (!design.empty() && isspace(design.front())) design.erase(0, 1);
            while (!design.empty() && isspace(design.back())) design.pop_back();
            
            if (!design.empty()) {
                memo.clear();
                if (isPossible(string_view(design), towels)) {
                    possibleCount++;
                }
            }
        }
    }

    cout << possibleCount << endl;
    return 0;
}