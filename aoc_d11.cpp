#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<long long> blink(const vector<long long>& stones) {
    vector<long long> result;

    for (const auto& stone : stones) {
        if (stone == 0) {
            result.push_back(1);
        } else {
            string stoneStr = to_string(stone);

            if (stoneStr.length() % 2 == 0) {
                int halfLen = stoneStr.length() / 2;

                string left = stoneStr.substr(0, halfLen);
                string right = stoneStr.substr(halfLen);

                if (!left.empty()) result.push_back(stoll(left));
                if (!right.empty()) result.push_back(stoll(right));
            } else {
                result.push_back(stone * 2024);
            }
        }
    }

    return result;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    vector<long long> stones;
    long long stone;

    while (cin >> stone) {
        stones.push_back(stone);
    }

    for (int i = 0; i < 25; ++i) {
        stones = blink(stones);
    }

    cout << stones.size();

    return 0;
}