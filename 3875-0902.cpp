/*
 * LeetCode 3875. Construct Uniform Parity Array I
 * Difficulty: Easy
 * Date: 2026-09-02
 *
 * You are given an array nums1 of n distinct integers.
 *
 * You want to construct another array nums2 of length n such that every
 * element in nums2 is odd, or every element is even.
 *
 * For each index i, you must choose exactly one of the following:
 *
 *   nums2[i] = nums1[i]
 *   nums2[i] = nums1[i] - nums1[j]   for some index j != i
 *
 * Return true if such an array can be constructed, otherwise return false.
 *
 * Example 1:
 *   Input:  nums1 = [2, 3]
 *   Output: true
 *   Choose nums2[0] = 2 - 3 = -1, nums2[1] = 3
 *   nums2 = [-1, 3], both odd.
 *
 * Example 2:
 *   Input:  nums1 = [4, 6]
 *   Output: true
 *   Choose nums2[0] = 4, nums2[1] = 6
 *   nums2 = [4, 6], both even.
 *
 * Constraints:
 *   1 <= n == nums1.length <= 100
 *   1 <= nums1[i] <= 100
 *   nums1 consists of distinct integers
 */

#include <vector>

using namespace std;

class Solution {
public:
    // 只关心奇偶。偶-偶/奇-奇=偶，偶-奇/奇-偶=奇。
    // 全偶或全奇：原样留下即可。
    // 奇偶都有：奇数留下，偶数减去任意一个奇数，nums2 全为奇数。
    // 三种情况都能构造，答案恒为 true。
    bool uniformArray(vector<int>& nums1) {
        return true;
    }
};
