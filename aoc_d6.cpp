#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main() {
    #ifndef ONLINE_JUDGE  
    freopen("input.txt", "r", stdin);  
    freopen("output.txt", "w", stdout);
    #endif 
    
    vector<string> lines;
    string input;

    while(getline(cin, input)){
        lines.push_back(input);
    }

    int height = lines.size();
    int width = lines[0].length();

    pair<int, int> curr{-1, -1};
    int dir = 0;
    for(int r=0; r<height; r++){
        for(int c=0; c<width; c++){
            if(lines[r][c] == '^'){
                curr = {r, c};
                lines[r][c] = '.';
            }
        }
    }

    set<pair<int, int>> visited;
    while(true){
        visited.insert(curr);
        int r2 = curr.first + dirs[dir].first;
        int c2 = curr.second + dirs[dir].second;
        if(!(0 <= r2 && r2 < height && 0 <= c2 && c2 < width)){
            break;
        }
        if(lines[r2][c2] == '.'){
            curr = {r2, c2};
        } else{
            dir = (dir + 1) % 4;
        }
    }
    cout << visited.size() << endl;

    return 0;
}