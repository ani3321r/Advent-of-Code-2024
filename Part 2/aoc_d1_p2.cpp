#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<int> l, r;
    string line;

    while (getline(cin, line)) {
        stringstream ss(line);
        int a, b;
        ss >> a >> b;
        l.push_back(a);
        r.push_back(b);
    }

    unordered_map<int, int> r_count;
    for (int num : r) {
        r_count[num]++;
    }

    int sum = 0;
    for (int num : l) {
        sum += num * r_count[num];
    }

    cout << sum;

    return 0;
}