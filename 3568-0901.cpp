/*
 * LeetCode 3568. Minimum Moves to Clean the Classroom
 * Difficulty: Medium
 * Date: 2026-09-01
 *
 * You are given an m x n grid classroom. A student volunteer must collect all
 * litter. Each cell is one of:
 *
 *   'S'  starting position of the student
 *   'L'  litter that must be collected (becomes empty once collected)
 *   'R'  reset area: restore energy to full capacity (can be used many times)
 *   'X'  obstacle (cannot pass)
 *   '.'  empty space
 *
 * energy is the student's maximum energy. The student starts at 'S' with this
 * energy. Each move to an adjacent cell (up / down / left / right) costs 1
 * energy. If energy becomes 0, the student can continue only when standing on
 * an 'R', which restores energy to the maximum.
 *
 * Return the minimum number of moves needed to collect all litter, or -1 if
 * it is impossible.
 *
 * Example 1:
 *   Input:  classroom = ["S.", "XL"], energy = 2
 *   Output: 2
 *   Path:   (0,0) -> (0,1) -> (1,1)
 *
 * Example 2:
 *   Input:  classroom = ["LS", "RL"], energy = 4
 *   Output: 3
 *   Path:   (0,1) -> (0,0) -> (1,0) -> (1,1)
 *
 * Example 3:
 *   Input:  classroom = ["L.S", "RXL"], energy = 3
 *   Output: -1
 *
 * Constraints:
 *   1 <= m == classroom.length <= 20
 *   1 <= n == classroom[i].length <= 20
 *   classroom[i][j] is one of 'S', 'L', 'R', 'X', '.'
 *   1 <= energy <= 50
 *   Exactly one 'S'
 *   At most 10 'L' cells
 */

#include <queue>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // 最短路：每走一步代价都是 1，所以用按层 BFS。
    // 普通网格 BFS 不够，因为同一格会在「不同剩余体力 / 不同已捡垃圾」下
    // 被多次走到，这些情况不能互相替代。
    int minMoves(vector<string>& classroom, int energy) {
        const int m = (int)classroom.size();   // 行数
        const int n = (int)classroom[0].size(); // 列数
        // 上下左右四邻接，对应题目「只能走到相邻格子」
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // litterId[i][j]：若该格是垃圾，记下它是第几号（0..k-1）；
        // 否则为 -1。后面用 bitmask 的第 id 位表示「这堆垃圾捡没捡」。
        // 题目保证最多 10 个 L，所以 20x20 数组和 2^k 状态都够用。
        int litterId[20][20];
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                litterId[i][j] = -1;
            }
        }

        int sx = 0, sy = 0; // 起点 'S' 的坐标
        int k = 0;          // 垃圾总数，同时当编号计数器
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                } else if (classroom[i][j] == 'L') {
                    litterId[i][j] = k++;
                }
            }
        }
        // 没有垃圾可捡，人已经站在起点，步数为 0
        if (k == 0) {
            return 0;
        }

        // 例如 k=3 时 allLitter = 0b111，mask 等于它表示三堆都捡完
        const int allLitter = (1 << k) - 1;

        // best[x][y][mask]：到达 (x,y) 且已捡集合为 mask 时，见过的最大剩余体力。
        // 剪枝依据：同一位置、同一已捡集合下，体力更高严格更优
        //（能走的路不少于体力更低的状态，碰到 R 也会被重置成同一个满值）。
        // 初值 -1 表示这个状态还没到达过。
        vector<vector<vector<int>>> best(
            m, vector<vector<int>>(n, vector<int>(1 << k, -1)));

        // BFS 节点：坐标、当前剩余体力、已捡垃圾的二进制集合
        struct State {
            int x, y, e, mask;
        };
        queue<State> q;
        // 起点：还没捡任何垃圾（mask=0），体力为满值 energy
        best[sx][sy][0] = energy;
        q.push({sx, sy, energy, 0});

        // 按层扩展：同一层里的状态步数相同，第一次捡完就是最少步数
        int steps = 0;
        while (!q.empty()) {
            // 先记下当前层大小，只处理这么多个，处理完 steps 加 1
            int sz = (int)q.size();
            while (sz--) {
                const State cur = q.front();
                q.pop();

                // 进入本层时已经收齐全部垃圾，当前 steps 就是答案
                if (cur.mask == allLitter) {
                    return steps;
                }
                // e<=0：体力耗尽且当前格不是刚重置后的满体力，无法再迈出一步
                // （若上一步走到 R，入队时 e 已经被设回 energy，不会走这里）
                // e < best：队列里的过时状态。后来可能有「同格同 mask 但体力更高」
                // 的节点入队，旧节点没有继续扩展的价值。
                if (cur.e <= 0 || cur.e < best[cur.x][cur.y][cur.mask]) {
                    continue;
                }

                for (const auto& d : dirs) {
                    const int nx = cur.x + d[0];
                    const int ny = cur.y + d[1];
                    // 越界或障碍，不能走
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n ||
                        classroom[nx][ny] == 'X') {
                        continue;
                    }

                    // 先扣 1 点体力；落到重置区再立刻回满（R 可反复使用）
                    int ne = cur.e - 1;
                    if (classroom[nx][ny] == 'R') {
                        ne = energy;
                    }

                    // 若新格是尚未记录过的垃圾，把对应 bit 置 1。
                    // 已经捡过则 |= 不改变 mask，格子当空地重复路过即可。
                    int nmask = cur.mask;
                    if (litterId[nx][ny] >= 0) {
                        nmask |= 1 << litterId[nx][ny];
                    }

                    // 这个 (格子, 已捡集合) 曾经用不少于 ne 的体力到达过，
                    // 当前走法不会更好，丢掉。
                    if (ne <= best[nx][ny][nmask]) {
                        continue;
                    }
                    best[nx][ny][nmask] = ne;
                    q.push({nx, ny, ne, nmask});
                }
            }
            ++steps; // 本层所有一步扩展结束，下一层步数 +1
        }
        // 队列空了还没收齐垃圾：体力、障碍或布局导致不可能
        return -1;
    }
};
