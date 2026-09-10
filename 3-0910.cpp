/*
 * LeetCode 3. Longest Substring Without Repeating Characters
 * Difficulty: Medium
 * Date: 2026-09-10
 *
 * Given a string s, find the length of the longest substring without
 * duplicate characters.
 *
 * Example 1:
 *   Input:  s = "abcabcbb"
 *   Output: 3
 *   "abc" (also "bca", "cab")
 *
 * Example 2:
 *   Input:  s = "bbbbb"
 *   Output: 1
 *
 * Example 3:
 *   Input:  s = "pwwkew"
 *   Output: 3
 *   "wke" is a substring; "pwke" is only a subsequence
 *
 * Constraints:
 *   0 <= s.length <= 10^5
 *   s consists of English letters, digits, symbols and spaces
 */

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // 滑动窗口：右端右移；若字符在窗口内重复，左端跳到上次出现位置的下一位。
    int lengthOfLongestSubstring(string s) {
        vector<int> last(128, -1);
        int ans = 0, left = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            const unsigned char c = s[i];
            if (last[c] >= left) {
                left = last[c] + 1;
            }
            last[c] = i;
            ans = max(ans, i - left + 1);
        }
        return ans;
    }
};
