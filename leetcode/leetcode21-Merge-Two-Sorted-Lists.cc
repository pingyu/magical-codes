#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using std::cout;
using std::vector;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode * p = &dummy;

        while (true) {
            if (l1 && l2) {
                if (l1->val < l2->val) {
                    p->next = l1;
                    l1 = l1->next;
                } else {
                    p->next = l2;
                    l2 = l2 -> next;
                }
                p = p->next;
            } else if (l1) {
                p->next = l1;
                break;
            } else { // if (l2)
                p->next = l2;
                break;
            }
        }
        
        return dummy.next;
    }
};

ListNode * make_list(const vector<int> & v) {
    ListNode dummy(0);
    ListNode * p = &dummy;
    for (auto n: v) {
        p->next = new ListNode(n);
        p = p->next;
    }
    return dummy.next;
}
void print_list(ListNode * list) {
    auto p = list;
    while (p) {
        cout << p->val << ",";
        p = p->next;
    }
}
struct Case {
    vector<int> l1;
    vector<int> l2;
};
int main() {
    Case cases[] = {
        {{1,2,4}, {1,3,4}},
        {{}, {}},
        {{1,2}, {}},
        {{10,11}, {1,2,3}},
    };
    Solution sln;
    for (auto& c: cases) {
        auto l1 = make_list(c.l1);
        print_list(l1);
        cout << "  +  ";
        auto l2 = make_list(c.l2);
        print_list(l2);
        cout << "  -->  ";
        print_list(sln.mergeTwoLists(l1, l2));
        cout << "\n";
    }
}
