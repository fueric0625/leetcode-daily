/*
 * LeetCode 1855. Maximum Distance Between a Pair of Values
 * Difficulty: Medium
 * Date: 2026-09-14
 *
 * You are given two non-increasing 0-indexed arrays nums1 and nums2.
 *
 * A pair (i, j) is valid if i <= j and nums1[i] <= nums2[j].
 * Its distance is j - i.
 *
 * Return the maximum distance of any valid pair, or 0 if none exist.
 *
 * Example 1:
 *   Input:  nums1 = [55, 30, 5, 4, 2], nums2 = [100, 20, 10, 10, 5]
 *   Output: 2
 *   Best pair (2, 4): 5 <= 5 and 4 - 2 = 2
 *
 * Example 2:
 *   Input:  nums1 = [2, 2, 2], nums2 = [10, 10, 1]
 *   Output: 1
 *
 * Example 3:
 *   Input:  nums1 = [30, 29, 19, 5], nums2 = [25, 25, 25, 25, 25]
 *   Output: 2
 *
 * Constraints:
 *   1 <= nums1.length, nums2.length <= 10^5
 *   1 <= nums1[i], nums2[j] <= 10^5
 *   Both arrays are non-increasing
 */

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    // 两数组都非递增：能配上就尽量把 j 右移拉大距离，配不上只能 i 右移让 nums1 变小。
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        const int n1 = (int)nums1.size();
        const int n2 = (int)nums2.size();
        int i = 0, j = 0, ans = 0;
        while (i < n1 && j < n2) {
            if (nums1[i] <= nums2[j]) {
                ans = max(ans, j - i);
                ++j;
            } else {
                ++i;
            }
        }
        return ans;
    }
};
