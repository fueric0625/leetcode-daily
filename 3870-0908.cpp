/*
 * LeetCode 3870. Count Commas in Range
 * Difficulty: Easy
 * Date: 2026-09-08
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
 *   1 <= n <= 10^5
 */

#include <algorithm>

using namespace std;

class Solution {
public:
    int countCommas(int n) {
        return max(n - 999, 0);
    }
};
