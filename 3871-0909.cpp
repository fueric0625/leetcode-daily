/*
 * LeetCode 3871. Count Commas in Range II
 * Difficulty: Medium
 * Date: 2026-09-09
 *
 * You are given an integer n.
 *
 * Return the total number of commas used when writing all integers from
 * [1, n] (inclusive) in standard number formatting.
 *
 * In standard formatting:
 *   A comma is inserted after every three digits from the right.
 *   Numbers with fewer than four digits contain no commas.
 *
 * Example 1:
 *   Input:  n = 1002
 *   Output: 3
 *   "1,000", "1,001", "1,002" each have one comma.
 *
 * Example 2:
 *   Input:  n = 998
 *   Output: 0
 *   Every number from 1 to 998 has fewer than four digits.
 *
 * Constraints:
 *   1 <= n <= 10^15
 */

class Solution {
public:
    // 每到 10^3、10^6、10^9… 这一档，[x, n] 里每个数都多一个逗号，贡献 n-x+1。
    long long countCommas(long long n) {
        long long ans = 0;
        for (long long x = 1000; x <= n; x *= 1000) {
            ans += n - x + 1;
        }
        return ans;
    }
};
