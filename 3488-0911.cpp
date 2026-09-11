/*
 * LeetCode 3488. Closest Equal Element Queries
 * Difficulty: Medium
 * Date: 2026-09-11
 *
 * You are given a circular array nums and an array queries.
 *
 * For each query i, find the minimum distance between index queries[i]
 * and any other index j such that nums[j] == nums[queries[i]].
 * If no such j exists, the answer is -1.
 *
 * Return an array answer of the same size as queries.
 *
 * Example 1:
 *   Input:  nums = [1, 3, 1, 4, 1, 3, 2], queries = [0, 3, 5]
 *   Output: [2, -1, 3]
 *   index 0 (value 1): nearest same value at 2, distance 2
 *   index 3 (value 4): unique, -1
 *   index 5 (value 3): nearest same at 1, circular distance 3
 *
 * Example 2:
 *   Input:  nums = [1, 2, 3, 4], queries = [0, 1, 2, 3]
 *   Output: [-1, -1, -1, -1]
 *
 * Constraints:
 *   1 <= queries.length <= nums.length <= 10^5
 *   1 <= nums[i] <= 10^6
 *   0 <= queries[i] < nums.length
 */

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    static int circDist(int a, int b, int n) {
        const int d = abs(a - b);
        return min(d, n - d);
    }

public:
    // 按值收集下标。环形上最近的相同值只可能是下标列表里的前驱或后继。
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        const int n = (int)nums.size();
        unordered_map<int, vector<int>> pos;
        pos.reserve(n * 2);
        for (int i = 0; i < n; ++i) {
            pos[nums[i]].push_back(i);
        }

        vector<int> best(n, n);
        for (auto& [_, ls] : pos) {
            const int m = (int)ls.size();
            if (m < 2) {
                continue;
            }
            for (int t = 0; t < m; ++t) {
                const int prev = ls[(t - 1 + m) % m];
                const int next = ls[(t + 1) % m];
                best[ls[t]] = min(circDist(ls[t], prev, n),
                                  circDist(ls[t], next, n));
            }
        }

        vector<int> ans;
        ans.reserve(queries.size());
        for (int q : queries) {
            ans.push_back(best[q] == n ? -1 : best[q]);
        }
        return ans;
    }
};
