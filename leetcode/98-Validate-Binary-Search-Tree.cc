// https://leetcode.com/problems/validate-binary-search-tree/

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

class Solution {
public:
    bool traverse(TreeNode* root, bool has_min, int min, bool has_max, int max) {
        if (!root) {
            return true;
        }
        if (has_min && root->val <= min) {
            return false;
        }
        if (has_max && root->val >= max) {
            return false;
        }
        if (!traverse(root->left, has_min, min, true, root->val)) {
            return false;
        }
        return traverse(root->right, true, root->val, has_max, max);
    }

    bool isValidBST(TreeNode* root) {
        return traverse(root, false, 0, false, 0);
    }
};

int main() {
    TreeNode * cases[] = {
        new TreeNode(2, new TreeNode(1), new TreeNode(3)),
        new TreeNode(5, new TreeNode(1),
            new TreeNode(4, new TreeNode(3), new TreeNode(6))
        ),
        nullptr,
        new TreeNode(10, new TreeNode(5),
            new TreeNode(15, new TreeNode(6), new TreeNode(20))
        ),
    };
    Solution sln;
    for (auto t: cases) {
        cout << sln.isValidBST(t) << "\n";
    }
    return 0;
}
