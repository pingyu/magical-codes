// https://leetcode.com/problems/recover-binary-search-tree/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <vector>
using std::vector;

class Solution {
public:
    void traverse(TreeNode* root, vector<TreeNode *>& nodes) {
        if (!root) {
            return;
        }
        traverse(root->left, nodes);
        nodes.push_back(root);
        traverse(root->right, nodes);
    }
    void recoverTree(TreeNode* root) {
        vector<TreeNode *> nodes;
        traverse(root, nodes);

        if (nodes.size() < 2) {
            return;
        }
        int i = 1;
        for (; i<nodes.size(); i++) {
            if (nodes[i-1]->val > nodes[i]->val) {
                break;
            }
        }
        int lhs = i - 1;
        for (; i<nodes.size(); i++) {
            if (nodes[i]->val > nodes[lhs]->val) {
                break;
            }
        }
        int rhs = i - 1;

        int tmp = nodes[lhs]->val;
        nodes[lhs]->val = nodes[rhs]->val;
        nodes[rhs]->val = tmp;
        return;
    }
};
