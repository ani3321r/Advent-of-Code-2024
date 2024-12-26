#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<pair<string, string>> edges;
    map<string, set<string>> conns;
    set<tuple<string, string, string>> sets;

    string line;
    while (getline(cin, line)) {
        size_t dash = line.find('-');
        string x = line.substr(0, dash);
        string y = line.substr(dash + 1);
        edges.emplace_back(x, y);
    }

    for (auto &[x, y] : edges) {
        conns[x].insert(y);
        conns[y].insert(x);
    }

    for (auto &[x, neighbors] : conns) {
        for (const string &y : neighbors) {
            for (const string &z : conns[y]) {
                if (x != z && conns[z].find(x) != conns[z].end()) {
                    vector<string> triangle = {x, y, z};
                    sort(triangle.begin(), triangle.end());
                    sets.insert(make_tuple(triangle[0], triangle[1], triangle[2]));
                }
            }
        }
    }

    int count = 0;
    for (const auto &s : sets) {
        if (get<0>(s).find('t') == 0 || get<1>(s).find('t') == 0 || get<2>(s).find('t') == 0) {
            count++;
        }
    }

    cout << count;

    return 0;
}