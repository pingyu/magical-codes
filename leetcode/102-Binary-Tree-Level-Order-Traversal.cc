// https://leetcode.com/problems/binary-tree-level-order-traversal/

#include <iostream>
#include <vector>
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <queue>

struct QueData {
    TreeNode * p;
    int step;
    QueData(TreeNode * p_, int step_): p(p_), step(step_) {}
};
using Que = std::queue<QueData>;
using Result = vector<vector<int>>;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        Result res;
        if (!root) {
            return res;
        }

        Que que;
        que.emplace(root, 1);
        while (!que.empty()) {
            QueData &d = que.front();
            if (d.step > res.size()) {
                res.emplace_back();
            }
            res.rbegin()->push_back(d.p->val);

            if (d.p->left) {
                que.emplace(d.p->left, d.step+1);
            }
            if (d.p->right) {
                que.emplace(d.p->right, d.step+1);
            }

            que.pop();
        }
        
        return res;
    }
};
