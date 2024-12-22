#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    string memory;
    getline(cin, memory, '\0');

    bool on = true;
    int total = 0;
    
    for (size_t i = 0; i < memory.size(); ++i) {
        if (memory.substr(i, 4) == "do()") {
            on = true;
            i += 3;
        } else if (memory.substr(i, 7) == "don't()") {
            on = false;
            i += 6;
        } else if (memory.substr(i, 4) == "mul(" && memory[i + 4] != '[' && memory[memory.find(')', i)] == ')') {
            if (on) {
                i += 4;
                int x = 0, y = 0;
                while (isdigit(memory[i])) {
                    x = x * 10 + (memory[i] - '0');
                    ++i;
                }
                if (memory[i] == ',') {
                    ++i;
                    while (isdigit(memory[i])) {
                        y = y * 10 + (memory[i] - '0');
                        ++i;
                    }
                    if (memory[i] == ')') {
                        total += x * y;
                    }
                }
            } else {
                while (memory[i] != ')' && i < memory.size()) {
                    ++i;
                }
            }
        }
    }

    cout << total << endl;
    return 0;
}