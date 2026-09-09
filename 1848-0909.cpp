/*
 * LeetCode 1848. Minimum Distance to the Target Element
 * Difficulty: Easy
 * Date: 2026-09-09
 *
 * Given a 0-indexed integer array nums and two integers target and start,
 * find an index i such that nums[i] == target and abs(i - start) is
 * minimized. Return abs(i - start).
 *
 * It is guaranteed that target exists in nums.
 *
 * Example 1:
 *   Input:  nums = [1, 2, 3, 4, 5], target = 5, start = 3
 *   Output: 1
 *   nums[4] == 5, abs(4 - 3) = 1
 *
 * Example 2:
 *   Input:  nums = [1], target = 1, start = 0
 *   Output: 0
 *
 * Example 3:
 *   Input:  nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1], target = 1, start = 0
 *   Output: 0
 *   nums[0] already matches, abs(0 - 0) = 0
 *
 * Constraints:
 *   1 <= nums.length <= 1000
 *   1 <= nums[i] <= 10^4
 *   0 <= start < nums.length
 *   target is in nums
 */

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    // 从 start 向两边扩：第一个碰到的 target 距离就是最小的。
    // 扩之前先判断下标是否还在数组里。
    int getMinDistance(vector<int>& nums, int target, int start) {
        const int n = (int)nums.size();
        const int lim = max(start, n - 1 - start);
        for (int d = 0; d <= lim; ++d) {
            if (start - d >= 0 && nums[start - d] == target) {
                return d;
            }
            if (start + d < n && nums[start + d] == target) {
                return d;
            }
        }
        return 0;
    }
};
