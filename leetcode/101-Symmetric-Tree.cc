// https://leetcode.com/problems/symmetric-tree/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool solve(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        if (p && q) {
            if (p->val != q->val) {
                return false;
            }
            if (!solve(p->left, q->right)) {
                return false;
            }
            return solve(p->right, q->left);
        }
        return false;
    }
    bool isSymmetric(TreeNode* root) {
        if (!root) {
            return true;
        }
        return solve(root->left, root->right);
    }
};
