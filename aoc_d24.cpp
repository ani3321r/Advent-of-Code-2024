#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <cmath>
#include <sstream>
using namespace std;

map<string, int> known;
map<string, tuple<string, string, string>> formulas;

int calc(string wire) {
    if (known.find(wire) != known.end()) 
        return known[wire];
    
    auto [op, x, y] = formulas[wire];
    
    if (op == "OR")
        known[wire] = calc(x) | calc(y);
    else if (op == "AND")
        known[wire] = calc(x) & calc(y);
    else
        known[wire] = calc(x) ^ calc(y);
    
    return known[wire];
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    string line, x, op, y, z;
    
    while (getline(cin, line)) {
        if (line.empty()) break;
        
        size_t pos = line.find(": ");
        x = line.substr(0, pos);
        known[x] = stoi(line.substr(pos + 2));
    }
    
    while (getline(cin, line)) {
        size_t pos = line.find(" ->");
        if (pos != string::npos) {
            line.replace(pos, 3, " ");
        }
        
        istringstream iss(line);
        iss >> x >> op >> y;
        iss >> z;
        iss >> x >> op >> y >> z;
        formulas[z] = make_tuple(op, x, y);
    }
    
    vector<int> z_values;
    for (int i = 0; ; i++) {
        string key = "z" + string(2 - to_string(i).length(), '0') + to_string(i);
        if (formulas.find(key) == formulas.end()) break;
        z_values.push_back(calc(key));
    }
    
    long long result = 0;
    for (int i = z_values.size() - 1; i >= 0; i--) {
        result = result * 2 + z_values[i];
    }
    
    cout << result;
    
    return 0;
}