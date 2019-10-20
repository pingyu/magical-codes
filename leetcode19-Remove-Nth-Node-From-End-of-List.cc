#include <iostream>
using std::cout;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head)
            return NULL;

        ListNode * tail = head;
        for (int i=0; i<n; i++) {
            tail = tail->next;
        }
        if (!tail)
            return head->next;
        
        ListNode * p = head;
        while (tail->next) {
            tail = tail->next;
            p = p->next;
        }
        p->next = p->next->next;
        return head;
    }
};

struct Case {
    int len;
    int n;
};

void print_list(ListNode * head) {
    ListNode * p = head;
    while (p) {
        cout << p->val << ",";
        p = p->next;
    }
    cout << "\n";
}
int main() {
    Case cases[] = {
        {5, 2},
        {2, 2},
    };
    Solution sln;
    for (auto& c: cases) {
        ListNode head(1);
        ListNode * pre = &head;
        for (int i=2; i<=c.len; i++) {
            pre->next = new ListNode(i);
            pre = pre->next;
        }
        print_list(&head);
        cout << "\n";

        print_list(sln.removeNthFromEnd(&head, c.n));
        cout << "\n";
        //TODO: release
    }
}
