/*
 * LeetCode 3876. Construct Uniform Parity Array II
 * Difficulty: Medium
 * Date: 2026-09-03
 *
 * You are given an array nums1 of n distinct integers.
 *
 * Construct nums2 of length n such that every element is odd, or every
 * element is even. For each index i, choose exactly one of:
 *
 *   nums2[i] = nums1[i]
 *   nums2[i] = nums1[i] - nums1[j]   for j != i, and nums1[i] - nums1[j] >= 1
 *
 * Return true if such an array can be constructed, otherwise false.
 *
 * Example 1:
 *   Input:  nums1 = [1, 4, 7]
 *   Output: true
 *   nums2 = [1, 4-1, 7] = [1, 3, 7], all odd
 *
 * Example 2:
 *   Input:  nums1 = [2, 3]
 *   Output: false
 *
 * Example 3:
 *   Input:  nums1 = [4, 6]
 *   Output: true
 *   nums2 = [4, 6], all even
 *
 * Constraints:
 *   1 <= n == nums1.length <= 10^5
 *   1 <= nums1[i] <= 10^9
 *   nums1 consists of distinct integers
 */

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    // 全奇或全偶：原样留下即可。
    // 又奇又偶时最小奇数变不成偶数，只能做成全奇：每个偶数必须能减去一个
    // 更小的奇数。存在偶数比最小奇数还小则失败，即要求 minOdd < minEven。
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX;
        int minEven = INT_MAX;
        for (int x : nums1) {
            if (x % 2 == 1) {
                minOdd = min(minOdd, x);
            } else {
                minEven = min(minEven, x);
            }
        }
        if (minOdd == INT_MAX || minEven == INT_MAX) {
            return true;
        }
        return minOdd < minEven;
    }
};
