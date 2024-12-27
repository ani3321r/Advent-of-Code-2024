#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;

unordered_map<string, long long> memo;

long long is_possible(const string &pattern, const vector<string> &stripes) {
    if (pattern.empty()) return 1;
    if (memo.count(pattern)) return memo[pattern];

    long long count = 0;
    for (const auto &stripe : stripes) {
        if (pattern.find(stripe) == 0) {
            count += is_possible(pattern.substr(stripe.size()), stripes);
        }
    }

    return memo[pattern] = count;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    string line;
    getline(cin, line);
    vector<string> stripes;
    size_t pos = 0;
    while ((pos = line.find(", ")) != string::npos) {
        stripes.push_back(line.substr(0, pos));
        line.erase(0, pos + 2);
    }
    stripes.push_back(line);

    getline(cin, line);

    vector<string> patterns;
    while (getline(cin, line)) {
        patterns.push_back(line);
    }

    long long total = 0;
    for (const auto &pattern : patterns) {
        total += is_possible(pattern, stripes);
    }

    cout << total << endl;

    return 0;
}