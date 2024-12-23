#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <cstdlib>

using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    map<int, pair<int, int>> files;
    vector<pair<int, int>> blanks;

    int fid = 0, pos = 0;
    string input;
    cin >> input;

    for (int i = 0; i < input.size(); ++i) {
        int x = input[i] - '0';
        if (i % 2 == 0) {
            if (x == 0) {
                return 1;
            }
            files[fid] = {pos, x};
            fid++;
        } else {
            if (x != 0) {
                blanks.push_back({pos, x});
            }
        }
        pos += x;
    }

    while (fid > 0) {
        fid--;
        auto [filePos, fileSize] = files[fid];
        for (size_t i = 0; i < blanks.size(); ++i) {
            auto [start, length] = blanks[i];
            if (start >= filePos) {
                blanks.erase(blanks.begin() + i, blanks.end());
                break;
            }
            if (fileSize <= length) {
                files[fid] = {start, fileSize};
                if (fileSize == length) {
                    blanks.erase(blanks.begin() + i);
                } else {
                    blanks[i] = {start + fileSize, length - fileSize};
                }
                break;
            }
        }
    }

    long long total = 0;
    for (const auto& [fid, fileData] : files) {
        auto [filePos, fileSize] = fileData;
        for (int x = filePos; x < filePos + fileSize; ++x) {
            total += static_cast<long long>(fid) * x;
        }
    }

    cout << total;

    return 0;
}