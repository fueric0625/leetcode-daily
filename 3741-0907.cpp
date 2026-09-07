/*
 * LeetCode 3741. Minimum Distance Between Three Equal Elements II
 * Difficulty: Medium
 * Date: 2026-09-07
 *
 * You are given an integer array nums.
 *
 * A tuple (i, j, k) of 3 distinct indices is good if
 *   nums[i] == nums[j] == nums[k]
 *
 * The distance of a good tuple is
 *   abs(i - j) + abs(j - k) + abs(k - i)
 *
 * Return the minimum possible distance of a good tuple, or -1 if none exist.
 *
 * Example 1:
 *   Input:  nums = [1, 2, 1, 1, 3]
 *   Output: 6
 *   Good tuple (0, 2, 3): nums are all 1
 *   abs(0-2) + abs(2-3) + abs(3-0) = 2 + 1 + 3 = 6
 *
 * Example 2:
 *   Input:  nums = [1, 1, 2, 3, 2, 1, 2]
 *   Output: 8
 *   Good tuple (2, 4, 6): nums are all 2
 *   abs(2-4) + abs(4-6) + abs(6-2) = 2 + 2 + 4 = 8
 *
 * Example 3:
 *   Input:  nums = [1]
 *   Output: -1
 *
 * Constraints:
 *   1 <= n == nums.length <= 10^5
 *   1 <= nums[i] <= n
 */

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    // 相同数字的下标有序。三个下标 i<j<k 的距离恒为 2*(k-i)，
    // 要最短只需看该数字下标列表里相邻的三个（即每隔一个的窗口）。
    int minimumDistance(vector<int>& nums) {
        const int n = (int)nums.size();
        vector<vector<int>> pos(n + 1);
        for (int i = 0; i < n; ++i) {
            pos[nums[i]].push_back(i);
        }
        int ans = INT_MAX;
        for (const auto& ls : pos) {
            for (int h = 0; h + 2 < (int)ls.size(); ++h) {
                ans = min(ans, (ls[h + 2] - ls[h]) * 2);
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
