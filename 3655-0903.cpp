/*
 * LeetCode 3655. XOR After Range Multiplication Queries II
 * Difficulty: Hard
 * Date: 2026-09-03
 *
 * Same operations as 3653, but n and q grow from 10^3 to 10^5.
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
 *
 * Example 2:
 *   Input:  nums = [2, 3, 1, 5, 4], queries = [[1, 4, 2, 3], [0, 2, 1, 2]]
 *   Output: 31
 *
 * Constraints:
 *   1 <= n == nums.length <= 10^5
 *   1 <= nums[i] <= 10^9
 *   1 <= q == queries.length <= 10^5
 *   queries[i] = [li, ri, ki, vi]
 *   0 <= li <= ri < n
 *   1 <= ki <= n
 *   1 <= vi <= 10^5
 *
 * Approach (sqrt split):
 *   Let B ~ sqrt(n). Multiplication is commutative, query order does not
 *   matter.
 *   k > B: at most n/k < B updates, brute-force multiply.
 *   k <= B: group by k. Indices with the same rem = i % k form a line.
 *   A query becomes a range multiply on that line; apply with a product
 *   difference array (diff[L] *= v, diff[R+1] *= inv(v)), then prefix
 *   product back onto nums.
 */

#include <cmath>
#include <vector>

using namespace std;

class Solution {
    static constexpr int MOD = 1'000'000'007;

    static long long modPow(long long a, long long e) {
        long long r = 1;
        a %= MOD;
        while (e > 0) {
            if (e & 1) {
                r = r * a % MOD;
            }
            a = a * a % MOD;
            e >>= 1;
        }
        return r;
    }

public:
    // k 大：更新次数少，直接乘。k 小：按 i%k 收成一条线，区间乘用乘积差分。
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const int n = (int)nums.size();
        int B = (int)sqrt(n);
        if (B < 1) {
            B = 1;
        }

        vector<vector<int>> byK(B + 1);
        for (int qi = 0; qi < (int)queries.size(); ++qi) {
            const int k = queries[qi][2];
            if (k > B) {
                const int l = queries[qi][0];
                const int r = queries[qi][1];
                const int v = queries[qi][3];
                for (int idx = l; idx <= r; idx += k) {
                    nums[idx] = (int)((long long)nums[idx] * v % MOD);
                }
            } else {
                byK[k].push_back(qi);
            }
        }

        for (int k = 1; k <= B; ++k) {
            if (byK[k].empty()) {
                continue;
            }
            vector<vector<long long>> diff(k);
            for (int rem = 0; rem < k; ++rem) {
                const int len = rem < n ? (n - 1 - rem) / k + 1 : 0;
                diff[rem].assign(len + 1, 1);
            }
            for (int qi : byK[k]) {
                const int l = queries[qi][0];
                const int r = queries[qi][1];
                const int v = queries[qi][3];
                const int rem = l % k;
                const int tL = l / k;
                const int last = l + (r - l) / k * k;
                const int tR = last / k;
                diff[rem][tL] = diff[rem][tL] * v % MOD;
                const long long inv = modPow(v, MOD - 2);
                diff[rem][tR + 1] = diff[rem][tR + 1] * inv % MOD;
            }
            for (int rem = 0; rem < k; ++rem) {
                const int len = (int)diff[rem].size() - 1;
                long long mul = 1;
                for (int t = 0; t < len; ++t) {
                    mul = mul * diff[rem][t] % MOD;
                    const int idx = rem + t * k;
                    nums[idx] = (int)((long long)nums[idx] * mul % MOD);
                }
            }
        }

        int ans = 0;
        for (int x : nums) {
            ans ^= x;
        }
        return ans;
    }
};
