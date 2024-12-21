#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool isValidSequence(const vector<int>& nums, size_t skipIndex) {
    if (nums.size() - 1 < 2) return true;
    
    bool validIncreasing = true;
    bool validDecreasing = true;
    int prevNum = -1;
    bool firstNum = true;
    
    for (size_t i = 0; i < nums.size(); i++) {
        if (i == skipIndex) continue;
        
        if (firstNum) {
            prevNum = nums[i];
            firstNum = false;
            continue;
        }
        
        int diff = nums[i] - prevNum;
        if (diff < 1 || diff > 3) validIncreasing = false;
        if (diff > -1 || diff < -3) validDecreasing = false;
        if (!validIncreasing && !validDecreasing) return false;
        
        prevNum = nums[i];
    }
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    string line;
    int validCount = 0;
    
    while (getline(cin, line)) {
        vector<int> numbers;
        istringstream iss(line);
        int num;
        while (iss >> num) numbers.push_back(num);
        
        for (size_t i = 0; i < numbers.size(); i++) {
            if (isValidSequence(numbers, i)) {
                validCount++;
                break;
            }
        }
    }
    
    cout << validCount << endl;
    return 0;
}