#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <bitset>

using namespace std;

vector<string> generatecombinations(int gap) {
    vector<string> combs;
    for (int i = 0; i < (1 << gap); i++) {
        combs.push_back(bitset<64>(i).to_string().substr(64 - gap));
    }
    return combs;
}

bool isValid(map<long long, vector<int>> eqs) {
    for (const auto& [testValue, operands] : eqs) {
        vector<string> combs = generatecombinations(operands.size() - 1);
        bool found = false;
        for (const auto& comb : combs) {
            long long sum = (comb[0] == '0') ? operands[0] + operands[1] : operands[0] * operands[1];
            for (size_t i = 2; i < operands.size(); i++) {
                if (comb[i - 1] == '0') {
                    sum += operands[i];
                } else {
                    sum *= operands[i];
                }
            }
            if (sum == testValue) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main() {
    #ifndef ONLINE_JUDGE  
    freopen("input.txt", "r", stdin);  
    freopen("output.txt", "w", stdout);
    #endif 
    
    vector<string> lines;
    string input;

    while (getline(cin, input)) {
        lines.push_back(input);
    }

    map<long long, vector<int>> dataMap;

    for (const auto& line : lines) {
        istringstream stream(line);
        string keyStr;
        
        if (!getline(stream, keyStr, ':')) continue;
        
        try {
            long long key = stoll(keyStr);
            vector<int> values;
            int value;
            while (stream >> value) {
                values.push_back(value);
            }
            if (!values.empty()) {
                dataMap[key] = values;
            }
        } catch (const exception& e) {
            cerr << "Invalid input line: " << line << endl;
        }
    }

    long long sumOfTests = 0;

    for (const auto& [testValue, operands] : dataMap) {
        map<long long, vector<int>> singleEntry = { {testValue, operands} };

        if (isValid(singleEntry)) {
            sumOfTests += testValue;
        }
    }

    cout << sumOfTests << endl;
    return 0;
}