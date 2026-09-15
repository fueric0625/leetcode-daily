/*
 * LeetCode 2472. Maximum Number of Non-overlapping Palindrome Substrings
 * Difficulty: Hard
 * Date: 2026-09-15
 *
 * You are given a string s and a positive integer k.
 *
 * Select as many non-overlapping substrings as possible such that:
 *   each substring has length at least k
 *   each substring is a palindrome
 *
 * Return the size of an optimal selection.
 *
 * Example 1:
 *   Input:  s = "abaccdbbd", k = 3
 *   Output: 2
 *   "aba" and "dbbd"
 *
 * Example 2:
 *   Input:  s = "adbcda", k = 2
 *   Output: 0
 *
 * Constraints:
 *   1 <= k <= s.length <= 2000
 *   s consists of lowercase English letters
 */

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    int maxPalindromes(string s, int k) {
        const int n = (int)s.size();

        // pal[l][r]：s[l..r] 是否回文。由短到长：
        // 两端字符相同，且中间 pal[l+1][r-1] 为真（长度 1、2 时中间为空）。
        vector<vector<char>> pal(n, vector<char>(n, 0));
        for (int len = 1; len <= n; ++len) {
            for (int l = 0; l + len - 1 < n; ++l) {
                const int r = l + len - 1;
                if (s[l] == s[r] && (len <= 2 || pal[l + 1][r - 1])) {
                    pal[l][r] = 1;
                }
            }
        }

        // 更长回文的中心仍是 k 或 k+1 的回文，贪心只关心结束更早，
        // 所以候选区间只收这两种长度。
        vector<pair<int, int>> segs;
        for (int l = 0; l < n; ++l) {
            const int r1 = l + k - 1;
            if (r1 < n && pal[l][r1]) {
                segs.push_back({l, r1});
            }
            const int r2 = l + k;
            if (r2 < n && pal[l][r2]) {
                segs.push_back({l, r2});
            }
        }

        // 活动安排：结束早的优先。选中后下一段起点必须 > 当前右端。
        sort(segs.begin(), segs.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second < b.second;
             });

        int ans = 0;
        int last = -1;  // 上一段右端，下一段需要 l > last
        for (const auto& [l, r] : segs) {
            if (l > last) {
                ++ans;
                last = r;
            }
        }
        return ans;
    }
};
