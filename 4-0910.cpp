/*
 * LeetCode 4. Median of Two Sorted Arrays
 * Difficulty: Hard
 * Date: 2026-09-10
 *
 * Given two sorted arrays nums1 and nums2 of size m and n, return the
 * median of the two sorted arrays.
 *
 * The overall run time complexity should be O(log (m + n)).
 *
 * Example 1:
 *   Input:  nums1 = [1, 3], nums2 = [2]
 *   Output: 2.00000
 *   merged = [1, 2, 3], median is 2
 *
 * Example 2:
 *   Input:  nums1 = [1, 2], nums2 = [3, 4]
 *   Output: 2.50000
 *   merged = [1, 2, 3, 4], median is (2 + 3) / 2 = 2.5
 *
 * Constraints:
 *   nums1.length == m, nums2.length == n
 *   0 <= m <= 1000
 *   0 <= n <= 1000
 *   1 <= m + n <= 2000
 *   -10^6 <= nums1[i], nums2[i] <= 10^6
 */

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    // 在较短数组上二分切分点 i，另一边取 j = k-i，使左半一共 k=(m+n+1)/2 个数。
    // 合法条件：Aleft<=Bright 且 Bleft<=Aright。复杂度 O(log(min(m,n)))，
    // 比题目要求的 O(log(m+n)) 更紧，因为 min(m,n) <= m+n。
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        const int m = (int)nums1.size();
        const int n = (int)nums2.size();
        const int k = (m + n + 1) / 2;
        int lo = 0, hi = m;
        while (lo <= hi) {
            const int i = (lo + hi) / 2;
            const int j = k - i;
            const int Aleft = (i == 0) ? INT_MIN : nums1[i - 1];
            const int Aright = (i == m) ? INT_MAX : nums1[i];
            const int Bleft = (j == 0) ? INT_MIN : nums2[j - 1];
            const int Bright = (j == n) ? INT_MAX : nums2[j];
            if (Aleft <= Bright && Bleft <= Aright) {
                if ((m + n) % 2 == 1) {
                    return max(Aleft, Bleft);
                }
                return (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0;
            }
            if (Aleft > Bright) {
                hi = i - 1;
            } else {
                lo = i + 1;
            }
        }
        return 0;
    }
};

/*
 * 切分注释（对应上面 i / j / 四个边界）
 *
 * k = (m+n+1)/2：左半要装的个数。i 是 nums1 左半长度，j = k-i 是 nums2 左半长度。
 *
 * nums1: [ 前 i 个 | 后面 ]     Aleft = nums1[i-1]，Aright = nums1[i]
 * nums2: [ 前 j 个 | 后面 ]     Bleft = nums2[j-1]，Bright = nums2[j]
 * 某一侧为空时：左空用 INT_MIN，右空用 INT_MAX，比较仍然成立。
 *
 * 切对了当且仅当：Aleft <= Bright 且 Bleft <= Aright
 *   （nums1 左半最大 <= nums2 右半最小，且 nums2 左半最大 <= nums1 右半最小）
 * 否则 Aleft > Bright 说明 nums1 左半拿多了，i 减小；反之 i 增大。
 *
 * 奇数中位数 = max(Aleft, Bleft)
 * 偶数中位数 = (max(Aleft, Bleft) + min(Aright, Bright)) / 2
 */
