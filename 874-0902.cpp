/*
 * LeetCode 874. Walking Robot Simulation
 * Difficulty: Medium
 * Date: 2026-09-02
 *
 * A robot on an infinite XY-plane starts at (0, 0) facing north. It receives
 * an array commands:
 *
 *   -2: turn left 90 degrees
 *   -1: turn right 90 degrees
 *    k (1 <= k <= 9): move forward k units, one unit at a time
 *
 * Some cells are obstacles: obstacles[i] = (xi, yi). If the next unit would
 * hit an obstacle, the robot stays on the block adjacent to it and continues
 * with the next command.
 *
 * Return the maximum squared Euclidean distance the robot ever reaches
 * (if the distance is 5, return 25).
 *
 * Notes:
 *   There can be an obstacle at (0, 0). The robot ignores it until it leaves
 *   the origin, then cannot return to (0, 0).
 *   North = +Y, East = +X, South = -Y, West = -X
 *
 * Example 1:
 *   Input:  commands = [4, -1, 3], obstacles = []
 *   Output: 25
 *   (0,0) north 4 -> (0,4); turn right; east 3 -> (3,4)
 *   max = 3^2 + 4^2 = 25
 *
 * Example 2:
 *   Input:  commands = [4, -1, 4, -2, 4], obstacles = [[2, 4]]
 *   Output: 65
 *   north 4 -> (0,4); turn right; blocked at (2,4) so stop at (1,4);
 *   turn left; north 4 -> (1,8)
 *   max = 1^2 + 8^2 = 65
 *
 * Example 3:
 *   Input:  commands = [6, -1, -1, 6], obstacles = [[0, 0]]
 *   Output: 36
 *   north 6 -> (0,6); turn right twice; south blocked by (0,0), stop at (0,1)
 *   max = 6^2 = 36
 *
 * Constraints:
 *   1 <= commands.length <= 10^4
 *   commands[i] is -2, -1, or an integer in [1, 9]
 *   0 <= obstacles.length <= 10^4
 *   -3 * 10^4 <= xi, yi <= 3 * 10^4
 *   The answer is guaranteed to be less than 2^31
 */

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    // 模拟：维护坐标、朝向，记下路径上最大的 x^2+y^2。
    // 方向按 北东南北西 循环；右转 dir+1，左转 dir+3。
    // 前进必须一格一格走，下一格是障碍则停住并结束本条指令。
    // (0,0) 的障碍放进集合即可：开局已在原点，不影响出发，离开后无法走回。
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        const int dx[4] = {0, 1, 0, -1};
        const int dy[4] = {1, 0, -1, 0};

        auto pack = [](int x, int y) -> long long {
            return (static_cast<long long>(x) << 32) |
                   static_cast<unsigned int>(y);
        };

        unordered_set<long long> blocked;
        blocked.reserve(obstacles.size() * 2);
        for (const auto& p : obstacles) {
            blocked.insert(pack(p[0], p[1]));
        }

        int x = 0, y = 0, dir = 0, ans = 0;
        for (int cmd : commands) {
            if (cmd == -1) {
                dir = (dir + 1) % 4;
                continue;
            }
            if (cmd == -2) {
                dir = (dir + 3) % 4;
                continue;
            }
            for (int step = 0; step < cmd; ++step) {
                const int nx = x + dx[dir];
                const int ny = y + dy[dir];
                if (blocked.count(pack(nx, ny))) {
                    break;
                }
                x = nx;
                y = ny;
                ans = max(ans, x * x + y * y);
            }
        }
        return ans;
    }
};
