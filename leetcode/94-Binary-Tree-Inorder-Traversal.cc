// https://leetcode.com/problems/binary-tree-inorder-traversal/

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <stack>
#include <unordered_set>
class Solution {
public:

    vector<int> inorderTraversal(TreeNode* root) {
        std::stack<TreeNode *> stack;
        std::unordered_set<TreeNode *> visited;

        vector<int> res;
        if (!root) {
            return res;
        }

        stack.push(root);
        while (!stack.empty()) {
            TreeNode * p = stack.top();
            if (p->left && visited.end() == visited.find(p)) {
                stack.push(p->left);
                // p->left = nullptr; // NOTICE!
                visited.insert(p);
                continue;
            }

            res.push_back(p->val);
            stack.pop();

            if (p->right) {
                stack.push(p->right);
            }
        }

        return res;
    }
};


int main() {
    TreeNode * cases[] = {
        new TreeNode(1, nullptr, new TreeNode(2, 
            new TreeNode(3, nullptr, nullptr), nullptr
        )),
        nullptr,
    };
    Solution sln;
    for (auto &c: cases) {
        auto res = sln.inorderTraversal(c);
        for (auto i: res) {
            cout << i << " ";
        }
        cout << "\n";
    }
    return 0;
}
