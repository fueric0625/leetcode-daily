/*
 * LeetCode 3483. Unique 3-Digit Even Numbers
 * Difficulty: Easy
 * Date: 2026-09-11
 *
 * Given an array of digits, return how many distinct three-digit even
 * numbers can be formed. Each copy of a digit may be used once per number.
 * Leading zeros are not allowed.
 *
 * Example 1:
 *   Input:  digits = [1, 2, 3, 4]
 *   Output: 12
 *   124, 132, 134, 142, 214, 234, 312, 314, 324, 342, 412, 432
 *
 * Example 2:
 *   Input:  digits = [0, 2, 2]
 *   Output: 2
 *   202, 220
 *
 * Example 3:
 *   Input:  digits = [6, 6, 6]
 *   Output: 1
 *
 * Example 4:
 *   Input:  digits = [1, 3, 5]
 *   Output: 0
 *
 * Constraints:
 *   3 <= digits.length <= 10
 *   0 <= digits[i] <= 9
 */

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    // n <= 10，枚举三个不同下标组成百/十/个位，个位偶数、百位非 0，用 set 去重。
    int totalNumbers(vector<int>& digits) {
        unordered_set<int> seen;
        const int n = (int)digits.size();
        for (int i = 0; i < n; ++i) {
            if (digits[i] == 0) {
                continue;
            }
            for (int j = 0; j < n; ++j) {
                if (j == i) {
                    continue;
                }
                for (int k = 0; k < n; ++k) {
                    if (k == i || k == j || digits[k] % 2 != 0) {
                        continue;
                    }
                    seen.insert(digits[i] * 100 + digits[j] * 10 + digits[k]);
                }
            }
        }
        return (int)seen.size();
    }
};
