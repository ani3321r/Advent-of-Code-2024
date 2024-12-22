#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

bool is_ordered(const vector<int>& update, const map<pair<int, int>, int>& cache) {
    for (size_t i = 0; i < update.size(); i++) {
        for (size_t j = i + 1; j < update.size(); j++) {
            auto key = make_pair(update[i], update[j]);
            if (cache.find(key) != cache.end() && cache.at(key) == 1) {
                return false;
            }
        }
    }
    return true;
}

bool cmp(const int& x, const int& y, const map<pair<int, int>, int>& cache) {
    auto key = make_pair(x, y);
    if (cache.find(key) != cache.end()) {
        return cache.at(key) < 0;
    }
    return false;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<pair<int, int>> rules;
    map<pair<int, int>, int> cache;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) break;
        stringstream ss(line);
        int x, y;
        char delimiter;
        ss >> x >> delimiter >> y;
        rules.emplace_back(x, y);
        cache[make_pair(x, y)] = -1;
        cache[make_pair(y, x)] = 1;
    }

    int total = 0;

    while (getline(cin, line)) {
        vector<int> update;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            update.push_back(stoi(token));
        }

        if (is_ordered(update, cache)) continue;

        sort(update.begin(), update.end(), [&](int a, int b) {
            return cmp(a, b, cache);
        });

        total += update[update.size() / 2];
    }

    cout << total << endl;

    return 0;
}