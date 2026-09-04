/*
 * LeetCode 3903. Smallest Stable Index I
 * Difficulty: Easy
 * Date: 2026-09-04
 *
 * You are given an integer array nums of length n and an integer k.
 *
 * For each index i, its instability score is
 *   max(nums[0..i]) - min(nums[i..n-1])
 *
 * Index i is stable if this score is <= k.
 * Return the smallest stable index, or -1 if none exists.
 *
 * Example 1:
 *   Input:  nums = [5, 0, 1, 4], k = 3
 *   Output: 3
 *   i=0: max[5]=5, min[5,0,1,4]=0 -> 5
 *   i=1: max[5,0]=5, min[0,1,4]=0 -> 5
 *   i=2: max[5,0,1]=5, min[1,4]=1 -> 4
 *   i=3: max[5,0,1,4]=5, min[4]=4 -> 1 <= 3
 *
 * Example 2:
 *   Input:  nums = [3, 2, 1], k = 1
 *   Output: -1
 *   scores are all 3-1=2 > 1
 *
 * Example 3:
 *   Input:  nums = [0], k = 0
 *   Output: 0
 *
 * Constraints:
 *   1 <= nums.length <= 100
 *   0 <= nums[i] <= 10^9
 *   0 <= k <= 10^9
 */

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    // n <= 100，对每个 i 重算左边 max、右边 min，找到第一个差值 <= k 的下标。
    int firstStableIndex(vector<int>& nums, int k) {
        const int n = (int)nums.size();
        for (int i = 0; i < n; ++i) {
            int leftMax = nums[0];
            for (int j = 1; j <= i; ++j) {
                leftMax = max(leftMax, nums[j]);
            }
            int rightMin = nums[i];
            for (int j = i + 1; j < n; ++j) {
                rightMin = min(rightMin, nums[j]);
            }
            if (leftMax - rightMin <= k) {
                return i;
            }
        }
        return -1;
    }
};
