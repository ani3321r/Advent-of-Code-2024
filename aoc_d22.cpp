#include <iostream>
using namespace std;

unsigned int step(unsigned int num) {
    const unsigned int MOD = 16777216;
    unsigned long long temp;

    temp = num * 64ULL;
    num = (num ^ temp) % MOD;

    temp = num / 32ULL;
    num = (num ^ temp) % MOD;

    temp = num * 2048ULL;
    num = (num ^ temp) % MOD;

    return num;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    unsigned long long total = 0;
    unsigned int num;

    while (cin >> num) {
        for (int i = 0; i < 2000; ++i) {
            num = step(num);
        }
        total += num;
    }

    cout << total;

    return 0;
}