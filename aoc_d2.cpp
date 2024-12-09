#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

bool strictly_increasing(const vector<int>& nums) {
    for(size_t i = 0; i < nums.size() - 1; i++) {
        if(nums[i] >= nums[i+1]) {
            return false;
        }
    }
    return true;
}

bool strictly_decreasing(const vector<int>& nums) {
    for(size_t i = 0; i < nums.size() - 1; i++) {
        if(nums[i] <= nums[i+1]) {
            return false;
        }
    }
    return true;
}

bool is_valid_differences(const vector<int>& nums) {
    for(size_t i = 0; i < nums.size() - 1; i++) {
        int diff = abs(nums[i+1] - nums[i]);
        if(diff <= 0 || diff > 3) {
            return false;
        }
    }
    return true;
}

int main(){

    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin); 
    freopen("output.txt","w",stdout);
    #endif

    vector<vector<int>> grid;
    string line;

    while(getline(cin, line)) {
        if(line.empty()) break;
        
        vector<int> current_line;
        stringstream ss(line);
        int num;
        while(ss >> num) {
            current_line.push_back(num);
        }
        grid.push_back(current_line);
    }

    vector<vector<int>> filtered_grid;
    for(auto& row : grid) {
        if(strictly_increasing(row) || strictly_decreasing(row)) {
            filtered_grid.push_back(row);
        }
    }

    for(auto& row : filtered_grid) {
        sort(row.begin(), row.end());
    }

    int total = 0;
    for(const auto& row : filtered_grid) {
        if(is_valid_differences(row)) {
            total++;
        }
    }
    
    cout << total << endl;

    return 0;
}