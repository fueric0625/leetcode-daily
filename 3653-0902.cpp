/*
 * LeetCode 3653. XOR After Range Multiplication Queries I
 * Difficulty: Medium
 * Date: 2026-09-02
 *
 * You are given an integer array nums of length n, and a 2D integer array
 * queries of size q, where queries[i] = [li, ri, ki, vi].
 *
 * For each query, do the following:
 *
 *   Set idx = li.
 *   While idx <= ri:
 *     nums[idx] = (nums[idx] * vi) % (10^9 + 7)
 *     idx += ki
 *
 * After processing all queries, return the bitwise XOR of every element
 * in nums.
 *
 * Example 1:
 *   Input:  nums = [1, 1, 1], queries = [[0, 2, 1, 4]]
 *   Output: 4
 *   The only query multiplies indices 0..2 by 4 -> [4, 4, 4]
 *   4 ^ 4 ^ 4 = 4
 *
 * Example 2:
 *   Input:  nums = [2, 3, 1, 5, 4], queries = [[1, 4, 2, 3], [0, 2, 1, 2]]
 *   Output: 31
 *   First query: indices 1, 3 *= 3 -> [2, 9, 1, 15, 4]
 *   Second query: indices 0, 1, 2 *= 2 -> [4, 18, 2, 15, 4]
 *   4 ^ 18 ^ 2 ^ 15 ^ 4 = 31
 *
 * Constraints:
 *   1 <= n == nums.length <= 10^3
 *   1 <= nums[i] <= 10^9
 *   1 <= q == queries.length <= 10^3
 *   queries[i] = [li, ri, ki, vi]
 *   0 <= li <= ri < n
 *   1 <= ki <= n
 *   1 <= vi <= 10^5
 */

#include <vector>

using namespace std;

class Solution {
public:
    // n、q 都 <= 1000，按查询逐个把 l, l+k, ... 乘上 v 再取模即可。
    // 乘法用 long long，避免溢出；最后把数组异或起来。
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const int MOD = 1'000'000'007;
        for (const auto& q : queries) {
            const int l = q[0], r = q[1], k = q[2], v = q[3];
            for (int idx = l; idx <= r; idx += k) {
                nums[idx] = (int)((long long)nums[idx] * v % MOD);
            }
        }
        int ans = 0;
        for (int x : nums) {
            ans ^= x;
        }
        return ans;
    }
};
