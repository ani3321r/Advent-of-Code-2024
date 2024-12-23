#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

bool can_obtain(long long target, vector<long long> array) {
    if (array.size() == 1) return target == array[0];

    long long last = array.back();
    array.pop_back();

    if (target % last == 0 && can_obtain(target / last, array)) {
        return true;
    }

    if (target > last && can_obtain(target - last, array)) {
        return true;
    }

    string s_target = to_string(target);
    string s_last = to_string(last);
    if (s_target.size() > s_last.size() && s_target.substr(s_target.size() - s_last.size()) == s_last) {
        long long new_target = stoll(s_target.substr(0, s_target.size() - s_last.size()));
        if (can_obtain(new_target, array)) {
            return true;
        }
    }

    return false;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    long long total = 0;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        size_t colon_pos = line.find(": ");
        if (colon_pos == string::npos) continue;

        long long target = stoll(line.substr(0, colon_pos));
        string right_part = line.substr(colon_pos + 2);
        istringstream iss(right_part);

        vector<long long> array;
        long long num;
        while (iss >> num) {
            array.push_back(num);
        }

        if (can_obtain(target, array)) {
            total += target;
        }
    }

    cout << total << endl;

    return 0;
}