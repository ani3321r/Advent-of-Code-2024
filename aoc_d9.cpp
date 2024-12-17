#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    #ifndef ONLINE_JUDGE  
    freopen("input.txt", "r", stdin);  
    freopen("output.txt", "w", stdout);
    #endif 
    
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    std::cin >> text;

    std::vector<std::string> map;
    map.reserve(1e7);

    int fileID = 0;

    for (size_t i = 0; i < text.length(); ++i) {
        bool definingFile = (i % 2 == 0);
        int n = text[i] - '0';

        if (definingFile) {
            for (int j = 0; j < n; ++j) {
                map.emplace_back(std::to_string(fileID));
            }
            fileID++;
        } else {
            for (int j = 0; j < n; ++j) {
                map.emplace_back(".");
            }
        }
    }

    size_t left = 0, right = map.size() - 1;
    while (left < right) {
        while (left < right && map[left] != ".") left++;
        while (left < right && map[right] == ".") right--;
        if (left < right) {
            std::swap(map[left], map[right]);
        }
    }

    long long sum = 0;
    for (size_t i = 0; i < map.size(); ++i) {
        if (map[i] == ".") continue;
        sum += i * std::stoll(map[i]);
    }

    std::cout << sum;
    return 0;
}