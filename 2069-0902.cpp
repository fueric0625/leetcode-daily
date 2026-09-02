/*
 * LeetCode 2069. Walking Robot Simulation II
 * Difficulty: Medium
 * Date: 2026-09-02
 *
 * A width x height grid on the XY-plane: bottom-left (0, 0), top-right
 * (width - 1, height - 1). A robot starts at (0, 0) facing East.
 *
 * Each step:
 *   Try to move one cell forward in the current direction.
 *   If that cell is out of bounds, turn 90 degrees counterclockwise and
 *   retry this same step.
 * After finishing the requested number of steps, the robot waits.
 *
 * Implement the Robot class:
 *
 *   Robot(int width, int height)
 *     Build a width x height grid, robot at (0, 0) facing East.
 *
 *   void step(int num)
 *     Move forward num steps (with the turn-on-out-of-bounds rule).
 *
 *   vector<int> getPos()
 *     Current cell [x, y].
 *
 *   string getDir()
 *     Current direction: "North", "East", "South", or "West".
 *
 * Example 1:
 *   Input:
 *     ["Robot", "step", "step", "getPos", "getDir",
 *      "step", "step", "step", "getPos", "getDir"]
 *     [[6, 3], [2], [2], [], [], [2], [1], [4], [], []]
 *   Output:
 *     [null, null, null, [4, 0], "East",
 *      null, null, null, [1, 2], "West"]
 *
 *   Robot robot(6, 3);  // (0, 0), East
 *   robot.step(2);      // (2, 0), East
 *   robot.step(2);      // (4, 0), East
 *   robot.getPos();     // [4, 0]
 *   robot.getDir();     // "East"
 *   robot.step(2);      // (5, 0) then out of bounds -> turn North -> (5, 1)
 *   robot.step(1);      // (5, 2), North
 *   robot.step(4);      // out of bounds -> turn West, then to (1, 2)
 *   robot.getPos();     // [1, 2]
 *   robot.getDir();     // "West"
 *
 * Constraints:
 *   2 <= width, height <= 100
 *   1 <= num <= 10^5
 *   At most 10^4 calls in total to step, getPos, and getDir
 */

#include <string>
#include <vector>

using namespace std;

class Robot {
    int w, h, x, y, dir;
    // 逆时针绕边界：东 -> 北 -> 西 -> 南
    static constexpr int dx[4] = {1, 0, -1, 0};
    static constexpr int dy[4] = {0, 1, 0, -1};
    static constexpr const char* kDir[4] = {"East", "North", "West", "South"};

public:
    // 机器人只会走矩形边界。num 很大时对周长取模，避免逐步走到 1e5。
    // 取模为 0 时要走整整一圈，不能当成 0 步：回到 (0,0) 时应朝南，
    // 和初始朝东不同。
    Robot(int width, int height) : w(width), h(height), x(0), y(0), dir(0) {}

    void step(int num) {
        const int peri = (w + h - 2) * 2;
        num %= peri;
        if (num == 0) {
            num = peri;
        }
        while (num--) {
            while (true) {
                const int nx = x + dx[dir];
                const int ny = y + dy[dir];
                if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
                    x = nx;
                    y = ny;
                    break;
                }
                dir = (dir + 1) % 4;
            }
        }
    }

    vector<int> getPos() { return {x, y}; }

    string getDir() { return kDir[dir]; }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */
