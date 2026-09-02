/*
 * LeetCode 2. Add Two Numbers
 * Difficulty: Medium
 * Date: 2026-09-02
 *
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order, and each node contains
 * a single digit.
 *
 * Add the two numbers and return the sum as a linked list in the same form.
 *
 * You may assume the two numbers do not contain any leading zero, except
 * the number 0 itself.
 *
 * Example 1:
 *   Input:  l1 = [2, 4, 3], l2 = [5, 6, 4]
 *   Output: [7, 0, 8]
 *   342 + 465 = 807
 *
 * Example 2:
 *   Input:  l1 = [0], l2 = [0]
 *   Output: [0]
 *
 * Example 3:
 *   Input:  l1 = [9, 9, 9, 9, 9, 9, 9], l2 = [9, 9, 9, 9]
 *   Output: [8, 9, 9, 9, 0, 0, 0, 1]
 *
 * Constraints:
 *   The number of nodes in each linked list is in the range [1, 100]
 *   0 <= Node.val <= 9
 *   It is guaranteed that the list represents a number that does not have
 *   leading zeros
 */

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    // 链表是逆序存的，从个位开始加，和竖式加法一样：同位相加再加进位。
    // 两条链长度可能不同，短的当 0；最后如果还有进位，补一个新节点。
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* tail = &dummy;
        int carry = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }
            carry = sum / 10;
            tail->next = new ListNode(sum % 10);
            tail = tail->next;
        }
        return dummy.next;
    }
};
