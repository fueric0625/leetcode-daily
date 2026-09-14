/*
 * LeetCode 836. Rectangle Overlap
 * Difficulty: Easy
 * Date: 2026-09-14
 *
 * An axis-aligned rectangle is [x1, y1, x2, y2]: bottom-left (x1, y1),
 * top-right (x2, y2).
 *
 * Two rectangles overlap if the area of their intersection is positive.
 * Touching only at a corner or an edge does not count.
 *
 * Return true if rec1 and rec2 overlap, otherwise false.
 *
 * Example 1:
 *   Input:  rec1 = [0, 0, 2, 2], rec2 = [1, 1, 3, 3]
 *   Output: true
 *
 * Example 2:
 *   Input:  rec1 = [0, 0, 1, 1], rec2 = [1, 0, 2, 1]
 *   Output: false
 *   They only share the edge x = 1.
 *
 * Example 3:
 *   Input:  rec1 = [0, 0, 1, 1], rec2 = [2, 2, 3, 3]
 *   Output: false
 *
 * Constraints:
 *   rec1.length == 4, rec2.length == 4
 *   -10^9 <= rec1[i], rec2[i] <= 10^9
 *   Both represent a valid rectangle with non-zero area
 */

#include <vector>

using namespace std;

class Solution {
public:
    // 不重叠：一个矩形完全在另一个的左 / 右 / 下 / 上（贴边也算）。
    // 四者都不成立才有正面积相交。
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        const bool separated =
            rec1[2] <= rec2[0] ||  // rec1 在 rec2 左侧（含贴边）
            rec2[2] <= rec1[0] ||  // rec1 在 rec2 右侧
            rec1[3] <= rec2[1] ||  // rec1 在 rec2 下方
            rec2[3] <= rec1[1];    // rec1 在 rec2 上方
        return !separated;
    }
};
