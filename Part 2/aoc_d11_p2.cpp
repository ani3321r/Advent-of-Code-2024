#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

unordered_map<string, long long> memo;

long long count(long long stone, int steps) {
    if (steps == 0) {
        return 1;
    }
    if (stone == 0) {
        return count(1, steps - 1);
    }

    string key = to_string(stone) + "_" + to_string(steps);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    string s = to_string(stone);
    int length = s.length();
    if (length % 2 == 0) {
        long long left = stoi(s.substr(0, length / 2));
        long long right = stoi(s.substr(length / 2));
        return memo[key] = count(left, steps - 1) + count(right, steps - 1);
    }

    return memo[key] = count(stone * 2024, steps - 1);
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<long long> stones;
    string line;
    getline(cin, line);
    stringstream ss(line);
    long long x;
    while (ss >> x) {
        stones.push_back(x);
    }

    long long total = 0;
    for (long long stone : stones) {
        total += count(stone, 75);
    }

    cout << total;
    return 0;
}