#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

struct Machine {
    int ax, ay, bx, by, prizeX, prizeY;
};

vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Machine parseMachine(const vector<string>& lines) {
    Machine machine;

    string lineA = lines[0].substr(lines[0].find(":") + 1);
    vector<string> partsA = split(lineA, ',');
    machine.ax = stoi(partsA[0].substr(partsA[0].find("+") + 1));
    machine.ay = stoi(partsA[1].substr(partsA[1].find("+") + 1));

    string lineB = lines[1].substr(lines[1].find(":") + 1);
    vector<string> partsB = split(lineB, ',');
    machine.bx = stoi(partsB[0].substr(partsB[0].find("+") + 1));
    machine.by = stoi(partsB[1].substr(partsB[1].find("+") + 1));

    string linePrize = lines[2].substr(lines[2].find(":") + 1);
    vector<string> partsPrize = split(linePrize, ',');
    machine.prizeX = stoi(partsPrize[0].substr(partsPrize[0].find("=") + 1));
    machine.prizeY = stoi(partsPrize[1].substr(partsPrize[1].find("=") + 1));

    return machine;
}

pair<int, int> solve(const Machine& machine) {
    for (int a = 0; a < 100; ++a) {
        for (int b = 0; b < 100; ++b) {
            int x = a * machine.ax + b * machine.bx;
            int y = a * machine.ay + b * machine.by;
            if (x == machine.prizeX && y == machine.prizeY) {
                return {a, b};
            }
        }
    }
    return {-1, -1};
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    string inputLine;
    vector<Machine> machines;

    while (getline(cin, inputLine)) {
        if (inputLine.empty()) continue;

        vector<string> groupLines;
        groupLines.push_back(inputLine);
        for (int i = 0; i < 2; ++i) {
            getline(cin, inputLine);
            groupLines.push_back(inputLine);
        }

        machines.push_back(parseMachine(groupLines));
    }

    int tokens = 0;
    for (const auto& machine : machines) {
        auto [a, b] = solve(machine);
        if (a != -1 && b != -1) {
            tokens += a * 3 + b * 1;
        }
    }

    cout << tokens << endl;
    return 0;
}