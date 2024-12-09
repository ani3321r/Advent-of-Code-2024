#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> parse_muls(const string& input) {
    vector<pair<int, int>> results;
    size_t i = 0;

    while (i < input.length()) {
        size_t mul_pos = input.find("mul(", i);
        if (mul_pos == string::npos) break;

        i = mul_pos + 4;
        string x, y;

        while (i < input.length() && isdigit(input[i])) {
            x += input[i];
            i++;
        }

        while (i < input.length() && (input[i] == ',' || isspace(input[i]))) {
            i++;
        }

        while (i < input.length() && isdigit(input[i])) {
            y += input[i];
            i++;
        }

        if (i < input.length() && input[i] == ')') {
            i++;

            if (!x.empty() && !y.empty() && x.length() <= 3 && y.length() <= 3) {
                results.push_back({stoi(x), stoi(y)});
            }
        }
    }

    return results;
}

int main(){

    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin); 
    freopen("output.txt","w",stdout);
    #endif

    vector<string> lines;
    string input;

    while(getline(cin, input)){
        lines.push_back(input);
    }

    long long total = 0;
    for(const auto& line : lines) {
        vector<pair<int, int>> results = parse_muls(line);
        for (const auto& expr : results) {
            total += expr.first * expr.second;
        }
    }
    
    cout << total;
    return 0;
}