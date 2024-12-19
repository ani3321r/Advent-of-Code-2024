#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct Robot {
    int x, y;
    int vx, vy;
};

inline pair<int, int> movePosition(int x, int y, int vx, int vy, int gridX, int gridY) {
    x = (x + vx + gridX) % gridX;
    y = (y + vy + gridY) % gridY;
    return {x, y};
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    vector<Robot> robots;

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        int px, py, vx, vy;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
        robots.push_back({px, py, vx, vy});
    }

    // here we can change the grid size according to the question
    const int gridX = 101, gridY = 103;

    // here we can change the seconds elapsed
    for (int i = 0; i < 100; i++) {
        for (auto &robot : robots) {
            tie(robot.x, robot.y) = movePosition(robot.x, robot.y, robot.vx, robot.vy, gridX, gridY);
        }
    }

    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    int midX = gridX / 2;
    int midY = gridY / 2;

    for (const auto &robot : robots) {
        if (robot.x >= 0 && robot.x <= midX - 1 && robot.y >= 0 && robot.y <= midY - 1) q1++; 
        if (robot.x >= midX + 1 && robot.x <= gridX - 1 && robot.y >= 0 && robot.y <= midY - 1) q2++;
        if (robot.x >= 0 && robot.x <= midX - 1 && robot.y >= midY + 1 && robot.y <= gridY - 1) q3++;
        if (robot.x >= midX + 1 && robot.x <= gridX - 1 && robot.y >= midY + 1 && robot.y <= gridY - 1) q4++;
    }

    cout << q1 * q2 * q3 * q4 << endl;

    return 0;
}