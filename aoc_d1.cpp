#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <numeric>

int main(){

    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin); 
    freopen("output.txt","w",stdout);
    #endif

    std::vector<int> ln, rn;
    
    std::string line;
    
    while (std::getline(std::cin, line) && !line.empty()) {
        size_t space_pos = line.find("   ");
        
        if (space_pos != std::string::npos) {
            int left_num = std::stoi(line.substr(0, space_pos));
            int right_num = std::stoi(line.substr(space_pos + 3));
            
            ln.push_back(left_num);
            rn.push_back(right_num);
        }
    }

    std::sort(rn.begin(), rn.end());
    std::sort(ln.begin(), ln.end());

    std::vector<int> diffs;
    for (size_t i = 0; i < ln.size(); ++i) {
        int diff = std::abs(ln[i] - rn[i]);
        diffs.push_back(diff);
    }

    int sum = std::accumulate(diffs.begin(), diffs.end(), 0);

    std::cout << sum << std::endl;
      
}