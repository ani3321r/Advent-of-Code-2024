#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <string>
#include <utility>
#include <cmath>

using namespace std;

int rows, cols;

int sides(const set<pair<int, int>>& region) {
    map<pair<double, double>, pair<double, double>> edges;
    for (auto [r, c] : region) {
        for (auto [nr, nc] : vector<pair<int, int>>{{r+1, c}, {r-1, c}, {r, c+1}, {r, c-1}}) {
            if (region.count({nr, nc})) continue;
            double er = (r + nr) / 2.0;
            double ec = (c + nc) / 2.0;
            edges[{er, ec}] = {er - r, ec - c};
        }
    }
    
    set<pair<double, double>> seen;
    int side_count = 0;
    for (auto& [edge, direction] : edges) {
        if (seen.count(edge)) continue;
        seen.insert(edge);
        side_count++;
        auto [er, ec] = edge;
        if (fmod(er, 1.0) == 0) {
            for (int dr : {-1, 1}) {
                double cr = er + dr;
                while (edges.count({cr, ec}) && edges[{cr, ec}] == direction) {
                    seen.insert({cr, ec});
                    cr += dr;
                }
            }
        } else {
            for (int dc : {-1, 1}) {
                double cc = ec + dc;
                while (edges.count({er, cc}) && edges[{er, cc}] == direction) {
                    seen.insert({er, cc});
                    cc += dc;
                }
            }
        }
    }
    return side_count;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<string> grid;
    string line;
    while (cin >> line) {
        grid.push_back(line);
    }

    rows = grid.size();
    cols = grid[0].size();

    vector<set<pair<int, int>>> regions;
    set<pair<int, int>> seen;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (seen.count({r, c})) continue;

            seen.insert({r, c});
            set<pair<int, int>> region;
            region.insert({r, c});
            queue<pair<int, int>> q;
            q.push({r, c});
            char crop = grid[r][c];

            while (!q.empty()) {
                auto [cr, cc] = q.front();
                q.pop();
                for (auto [nr, nc] : vector<pair<int, int>>{{cr-1, cc}, {cr+1, cc}, {cr, cc-1}, {cr, cc+1}}) {
                    if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
                    if (grid[nr][nc] != crop) continue;
                    if (region.count({nr, nc})) continue;
                    region.insert({nr, nc});
                    q.push({nr, nc});
                }
            }
            seen.insert(region.begin(), region.end());
            regions.push_back(region);
        }
    }

    int total = 0;
    for (const auto& region : regions) {
        total += region.size() * sides(region);
    }

    cout << total;
    return 0;
}