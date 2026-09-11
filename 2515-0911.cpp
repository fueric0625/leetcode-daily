/*
 * LeetCode 2515. Shortest Distance to Target String in a Circular Array
 * Difficulty: Easy
 * Date: 2026-09-11
 *
 * You are given a 0-indexed circular string array words and a string target.
 * words[i]'s next is words[(i + 1) % n], previous is words[(i - 1 + n) % n].
 *
 * Starting from startIndex, one step moves to the next or previous word.
 * Return the shortest distance to target, or -1 if target is not in words.
 *
 * Example 1:
 *   Input:  words = ["hello","i","am","leetcode","hello"],
 *           target = "hello", startIndex = 1
 *   Output: 1
 *   Nearest "hello" is at index 0, one step left.
 *
 * Example 2:
 *   Input:  words = ["a","b","leetcode"], target = "leetcode", startIndex = 0
 *   Output: 1
 *
 * Example 3:
 *   Input:  words = ["i","eat","leetcode"], target = "ate", startIndex = 0
 *   Output: -1
 *
 * Constraints:
 *   1 <= words.length <= 100
 *   1 <= words[i].length <= 100
 *   words[i] and target consist of lowercase English letters
 *   0 <= startIndex < words.length
 */

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // 枚举每个等于 target 的下标，环形距离取左右较近的一边，再取全局最小。
    int closetTarget(vector<string>& words, string target, int startIndex) {
        const int n = (int)words.size();
        int ans = n;
        for (int i = 0; i < n; ++i) {
            if (words[i] != target) {
                continue;
            }
            const int d = abs(i - startIndex);
            ans = min(ans, min(d, n - d));
        }
        return ans == n ? -1 : ans;
    }
};
