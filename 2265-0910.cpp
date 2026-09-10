/*
 * LeetCode 2265. Count Nodes Equal to Average of Subtree
 * Difficulty: Medium
 * Date: 2026-09-10
 *
 * Given the root of a binary tree, return the number of nodes whose value
 * equals the average of the values in its subtree.
 *
 * The average of n elements is sum / n, rounded down to the nearest integer.
 * A subtree of a node consists of that node and all of its descendants.
 *
 * Example 1:
 *   Input:  root = [4, 8, 5, 0, 1, null, 6]
 *   Output: 5
 *   Node 4: (4+8+5+0+1+6)/6 = 4
 *   Node 5: (5+6)/2 = 5
 *   Nodes 0, 1, 6: each is a single-node subtree
 *
 * Example 2:
 *   Input:  root = [1]
 *   Output: 1
 *
 * Constraints:
 *   The number of nodes is in the range [1, 1000]
 *   0 <= Node.val <= 1000
 */

#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
    int ans = 0;

    // 返回 {子树和, 节点数}；空树是 {0, 0}
    pair<int, int> dfs(TreeNode* node) {
        if (node == nullptr) {
            return {0, 0};
        }
        auto [ls, lc] = dfs(node->left);
        auto [rs, rc] = dfs(node->right);
        const int sum = ls + rs + node->val;
        const int cnt = lc + rc + 1;
        if (node->val == sum / cnt) {
            ++ans;
        }
        return {sum, cnt};
    }

public:
    // 后序 DFS：左右子树的和与个数加起来，再判断当前值是否等于整除平均。
    int averageOfSubtree(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};
