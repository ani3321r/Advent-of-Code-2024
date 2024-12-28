#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <tuple>

using namespace std;

long long step(long long num) {
    num = (num ^ (num * 64)) % 16777216;
    num = (num ^ (num / 32)) % 16777216;
    num = (num ^ (num * 2048)) % 16777216;
    return num;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    map<tuple<int, int, int, int>, long long> seq_to_total;
    string line;
    
    while (cin >> line) {
        long long num = stoll(line);
        vector<int> buyer;
        buyer.push_back(num % 10);
        
        for (int i = 0; i < 2000; i++) {
            num = step(num);
            buyer.push_back(num % 10);
        }
        
        set<tuple<int, int, int, int>> seen;
        for (int i = 0; i < buyer.size() - 4; i++) {
            int a = buyer[i];
            int b = buyer[i + 1];
            int c = buyer[i + 2];
            int d = buyer[i + 3];
            int e = buyer[i + 4];
            
            tuple<int, int, int, int> seq = make_tuple(b-a, c-b, d-c, e-d);
            if (seen.find(seq) != seen.end()) continue;
            seen.insert(seq);
            
            seq_to_total[seq] += e;
        }
    }
    
    long long max_val = 0;
    for (const auto& pair : seq_to_total) {
        max_val = max(max_val, pair.second);
    }
    
    cout << max_val << endl;
    
    return 0;
}