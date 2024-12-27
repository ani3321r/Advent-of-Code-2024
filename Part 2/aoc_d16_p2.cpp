#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <limits>
#include <tuple>
using namespace std;

struct StateHash {
    template <class T1, class T2, class T3, class T4>
    size_t operator()(const tuple<T1, T2, T3, T4>& t) const {
        auto h1 = hash<T1>{}(get<0>(t));
        auto h2 = hash<T2>{}(get<1>(t));
        auto h3 = hash<T3>{}(get<2>(t));
        auto h4 = hash<T4>{}(get<3>(t));
        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }

    int rows = grid.size();
    int cols = grid[0].size();

    int sr = -1, sc = -1;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 'S') {
                sr = r;
                sc = c;
                break;
            }
        }
        if (sr != -1) break;
    }

    using State = tuple<int, int, int, int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, sr, sc, 0, 1});

    map<tuple<int, int, int, int>, int> lowest_cost;
    lowest_cost[{sr, sc, 0, 1}] = 0;

    map<tuple<int, int, int, int>, set<tuple<int, int, int, int>>> backtrack;

    int best_cost = numeric_limits<int>::max();
    set<tuple<int, int, int, int>> end_states;

    while (!pq.empty()) {
        auto [cost, r, c, dr, dc] = pq.top();
        pq.pop();

        if (cost > lowest_cost[{r, c, dr, dc}]) continue;

        if (grid[r][c] == 'E') {
            if (cost > best_cost) break;
            best_cost = cost;
            end_states.insert({r, c, dr, dc});
        }

        vector<tuple<int, int, int, int, int>> next_moves = {
            {cost + 1, r + dr, c + dc, dr, dc},
            {cost + 1000, r, c, dc, -dr},
            {cost + 1000, r, c, -dc, dr}
        };

        for (const auto& [new_cost, nr, nc, ndr, ndc] : next_moves) {
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#') continue;

            auto it = lowest_cost.find({nr, nc, ndr, ndc});
            int lowest = (it == lowest_cost.end()) ? numeric_limits<int>::max() : it->second;

            if (new_cost > lowest) continue;

            if (new_cost < lowest) {
                backtrack[{nr, nc, ndr, ndc}].clear();
                lowest_cost[{nr, nc, ndr, ndc}] = new_cost;
            }

            backtrack[{nr, nc, ndr, ndc}].insert({r, c, dr, dc});
            pq.push({new_cost, nr, nc, ndr, ndc});
        }
    }

    deque<tuple<int, int, int, int>> states(end_states.begin(), end_states.end());
    set<tuple<int, int, int, int>> seen(end_states.begin(), end_states.end());

    while (!states.empty()) {
        auto current = states.front();
        states.pop_front();

        auto it = backtrack.find(current);
        if (it != backtrack.end()) {
            for (const auto& last : it->second) {
                if (seen.find(last) != seen.end()) continue;
                seen.insert(last);
                states.push_back(last);
            }
        }
    }

    set<pair<int, int>> unique_positions;
    for (const auto& [r, c, dr, dc] : seen) {
        unique_positions.insert({r, c});
    }

    cout << unique_positions.size();

    return 0;
}