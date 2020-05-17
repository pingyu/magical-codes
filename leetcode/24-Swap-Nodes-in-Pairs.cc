// https://leetcode.com/problems/swap-nodes-in-pairs/

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode mock(0, head);
        ListNode *p0 = &mock;
        while (1) {
            ListNode * p1 = p0->next;
            if (!p1) {
                return mock.next;
            }
            ListNode * p2 = p1->next;
            if (!p2) {
                return mock.next;
            }
            ListNode * p3 = p2->next;

            p0->next = p2;
            p2->next = p1;
            p1->next = p3;
            p0 = p1;
        }
    }
};

struct Case {
    vector<int> nums;
};
int main() {
    Case cases[] = {
        {{1, 2, 3, 4}},
        {},
        {{1, 2, 3, 4, 5}},
    };
    Solution sln;
    for (auto &c: cases) {
        ListNode head;
        ListNode *p0 = &head;
        for (auto i: c.nums) {
            auto p = new ListNode(i);
            p0->next = p;
            p0 = p;
        }
        ListNode * res = sln.swapPairs(head.next);
        while (res) {
            cout << res->val << " ";
            res = res->next;
        }
        cout << "\n";
    }
    return 0;
}
