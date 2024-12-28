#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

unordered_map<string, set<string>> conns;
set<vector<string>> sets;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void search(const string& node, set<string> req) {
    vector<string> key(req.begin(), req.end());
    sort(key.begin(), key.end());
    
    if (sets.find(key) != sets.end()) return;
    sets.insert(key);
    
    for (const string& neighbor : conns[node]) {
        if (req.find(neighbor) != req.end()) continue;
        
        bool valid = true;
        for (const string& query : req) {
            if (conns[query].find(neighbor) == conns[query].end()) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;
        
        set<string> new_req = req;
        new_req.insert(neighbor);
        search(neighbor, new_req);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        vector<string> edge = split(line, '-');
        string x = edge[0];
        string y = edge[1];
        
        if (conns.find(x) == conns.end()) conns[x] = set<string>();
        if (conns.find(y) == conns.end()) conns[y] = set<string>();
        conns[x].insert(y);
        conns[y].insert(x);
    }
    
    for (const auto& pair : conns) {
        set<string> initial = {pair.first};
        search(pair.first, initial);
    }
    
    vector<string> largest;
    for (const auto& set : sets) {
        if (set.size() > largest.size()) {
            largest = set;
        }
    }
    
    for (size_t i = 0; i < largest.size(); i++) {
        cout << largest[i];
        if (i < largest.size() - 1) cout << ",";
    }

    return 0;
}