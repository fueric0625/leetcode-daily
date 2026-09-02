/*
 * LeetCode 1. Two Sum
 * Difficulty: Easy
 * Date: 2026-09-02
 *
 * Given an integer array nums and an integer target, return the indices of
 * the two numbers such that they add up to target.
 *
 * You may assume that each input has exactly one solution, and you may not
 * use the same element twice. The answer can be returned in any order.
 *
 * Example 1:
 *   Input:  nums = [2, 7, 11, 15], target = 9
 *   Output: [0, 1]
 *   nums[0] + nums[1] == 9
 *
 * Example 2:
 *   Input:  nums = [3, 2, 4], target = 6
 *   Output: [1, 2]
 *
 * Example 3:
 *   Input:  nums = [3, 3], target = 6
 *   Output: [0, 1]
 *
 * Constraints:
 *   2 <= nums.length <= 10^4
 *   -10^9 <= nums[i] <= 10^9
 *   -10^9 <= target <= 10^9
 *   Exactly one valid answer exists
 *
 * Follow-up: a solution with time complexity better than O(n^2)
 */

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    // 一遍哈希：扫到 nums[i] 时，看 target-nums[i] 是否已出现过。
    // 用下标当值，保证返回的是两个不同位置。
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        for (int i = 0; i < (int)nums.size(); i++) {
            const int need = target - nums[i];
            auto it = seen.find(need);
            if (it != seen.end()) {
                return {it->second, i};
            }
            seen[nums[i]] = i;
        }
        return {};
    }
};

/*
 * 对话小结
 *
 * 1. seen 是 unordered_map<int,int>：键是数组里的数字，值是下标。
 *    例如见过 10,11,12 后：10->0, 11->1, 12->2，所以 seen[10]==0。
 *
 * 2. find(need) 按「键」查，need 是 int，和键的类型一致。
 *    查的不是整个 nums，也不是按下标查。找到则 it->second 是那个下标。
 *
 * 3. auto it = seen.find(need) 里 auto 让编译器自己填迭代器类型，
 *    等价于 unordered_map<int,int>::iterator it = ...
 *
 * 4. 同一键只能有一条记录，后写会覆盖下标。所以要先 find 再写入：
 *    [3,3] target=6 时，第二个 3 先查到第一个 3 的下标，再 return，
 *    不会用到自己。
 *
 * 5. for 第三段里 ++i 和 i++ 对循环次数没有区别；只有用到表达式
 *    的返回值时才分先后（++i 得新值，i++ 得旧值）。
 *
 * 6. seen[need] 在键不存在时会插入新项，所以查询用 find，不要直接 []。
 *
 * 过程（短）：[2,7,11,15] target=9
 *   i=0 值2 缺7 没有 -> 记下 2->0
 *   i=1 值7 缺2 有下标0 -> 返回 {0,1}
 *
 * 过程（长）：[10,11,12,13,14,15,16,1,2,3,4,5] target=9
 *   前面一直缺不到，表越记越大；最后 i=11 值5 缺4，表里有 4->10
 *   -> 返回 {10,11}
 */
