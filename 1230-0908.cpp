/*
 * LeetCode 1320. Minimum Distance to Type a Word Using Two Fingers
 * Difficulty: Hard
 * Date: 2026-09-08
 *
 * A custom keyboard of uppercase letters lies on the XY-plane.
 * For example: A is (0, 0), B is (0, 1), P is (2, 3), Z is (4, 1).
 * Layout is 6 columns: position of letter c is
 *   row = (c - 'A') / 6, col = (c - 'A') % 6.
 *
 * Given a string word, return the minimum total move distance to type it
 * using only two fingers. Distance between (x1, y1) and (x2, y2) is
 *   |x1 - x2| + |y1 - y2|.
 *
 * The initial positions of both fingers cost 0 and need not start on
 * the first letters.
 *
 * Example 1:
 *   Input:  word = "CAKE"
 *   Output: 3
 *   Finger1: C (0) -> A (2); Finger2: K (0) -> E (1); total 3
 *
 * Example 2:
 *   Input:  word = "HAPPY"
 *   Output: 6
 *   Finger1: H (0) -> A (2) -> Y (4); Finger2: P (0) -> P (0); total 6
 *
 * Constraints:
 *   2 <= word.length <= 300
 *   word[i] is an uppercase English letter
 */

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
    static int dist(int a, int b) {
        return abs(a / 6 - b / 6) + abs(a % 6 - b % 6);
    }

public:
    // 打完当前字母后，一根手指必在该字母上。dp[p] = 另一根在 p（26=未落下）的最小代价。
    // 下一字母：要么动刚按的那根，要么动另一根（未落下则免费）。
    int minimumDistance(string word) {
        const int INF = 1e9;
        const int n = (int)word.size();
        vector<int> dp(27, INF);
        dp[26] = 0; // 已打 word[0]，另一根还没落下

        for (int i = 0; i + 1 < n; ++i) {
            const int cur = word[i] - 'A';
            const int nxt = word[i + 1] - 'A';
            vector<int> ndp(27, INF);
            for (int p = 0; p <= 26; ++p) {
                if (dp[p] >= INF) {
                    continue;
                }
                ndp[p] = min(ndp[p], dp[p] + dist(cur, nxt));
                const int extra = (p == 26) ? 0 : dist(p, nxt);
                ndp[cur] = min(ndp[cur], dp[p] + extra);
            }
            dp.swap(ndp);
        }
        return *min_element(dp.begin(), dp.end());
    }
};
