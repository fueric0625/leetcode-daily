/*
 * LeetCode 940. Distinct Subsequences II
 * Difficulty: Hard
 * Date: 2026-09-07
 *
 * Given a string s, return the number of distinct non-empty subsequences
 * of s. Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * A subsequence is formed by deleting some (possibly none) of the
 * characters without changing the order of the rest.
 * "ace" is a subsequence of "abcde"; "aec" is not.
 *
 * Example 1:
 *   Input:  s = "abc"
 *   Output: 7
 *   "a", "b", "c", "ab", "ac", "bc", "abc"
 *
 * Example 2:
 *   Input:  s = "aba"
 *   Output: 6
 *   "a", "b", "ab", "aa", "ba", "aba"
 *
 * Example 3:
 *   Input:  s = "aaa"
 *   Output: 3
 *   "a", "aa", "aaa"
 *
 * Constraints:
 *   1 <= s.length <= 2000
 *   s consists of lowercase English letters
 */

#include <string>

using namespace std;

class Solution {
public:
    // total 含空串。读入 c 时，每个已有子序列都可在末尾接 c；
    // 若 c 出现过，会与旧的「以 c 结尾」重复，要减掉 end[c]。
    int distinctSubseqII(string s) {
        const int MOD = 1'000'000'007;
        long long total = 1;
        long long end[26] = {};
        for (char ch : s) {
            const int c = ch - 'a';
            const long long old = end[c];
            end[c] = total;
            total = (total * 2 - old) % MOD;
            if (total < 0) {
                total += MOD;
            }
        }
        return (int)((total - 1 + MOD) % MOD);
    }
};

/*
 * 思路
 *
 * n <= 2000，不能枚举 2^n 再去重。从左到右扫，维护：
 *   total  : 当前前缀的不同子序列个数（含空串）
 *   end[c] : 其中以字符 c 结尾的个数
 *
 * 新读入 c：每个已有子序列都可以接上这个 c，得到 total 个以 c 结尾的串。
 * 第一次出现 c 时总数变成 2*total；若以前有过 c，旧的 end[c] 会和这次
 * 接上 c 得到的一部分字符串相同，所以
 *   新 end[c] = 旧 total
 *   新 total  = 2 * 旧 total - 旧 end[c]  （模 1e9+7，差可能为负）
 *
 * 整串扫完，答案是 total-1（去掉空串）。
 *
 * "aba"：空=1
 *   a -> total=2  （空, a）
 *   b -> total=4  （空, a, b, ab）
 *   a -> total=7  （减掉旧的 "a"），非空 6
 * "aaa"：2 -> 3 -> 4（含空），非空 3
 */
