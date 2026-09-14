/*
 * LeetCode 3783. Mirror Distance of an Integer
 * Difficulty: Easy
 * Date: 2026-09-14
 *
 * You are given an integer n.
 * Its mirror distance is abs(n - reverse(n)), where reverse(n) is n with
 * digits reversed. Leading zeros after reversing are dropped
 * (e.g. reverse(10) = 1).
 *
 * Return the mirror distance of n.
 *
 * Example 1:
 *   Input:  n = 25
 *   Output: 27
 *   reverse(25) = 52, abs(25 - 52) = 27
 *
 * Example 2:
 *   Input:  n = 10
 *   Output: 9
 *   reverse(10) = 1, abs(10 - 1) = 9
 *
 * Example 3:
 *   Input:  n = 7
 *   Output: 0
 *
 * Constraints:
 *   1 <= n <= 10^9
 */

#include <cstdlib>

using namespace std;

class Solution {
public:
    // 按位弹出 n 的个位拼成反转数，末尾 0 会变成前导 0 自然丢掉。
    int mirrorDistance(int n) {
        int rev = 0;
        int x = n;
        while (x > 0) {
            rev = rev * 10 + x % 10;
            x /= 10;
        }
        return abs(n - rev);
    }
};
