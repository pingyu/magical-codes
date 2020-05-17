// https://leetcode.com/problems/unique-binary-search-trees-ii/

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<TreeNode *> traverse(int begin, int end) {
        vector<TreeNode *> trees;
        if (begin > end) {
            trees.push_back(nullptr);
            return trees;
        }
        for (int i=begin; i<=end; i++) {
            vector<TreeNode *> left = traverse(begin, i-1),
                               right = traverse(i+1, end);
            for (TreeNode *lp: left) {
                for (TreeNode *rp: right) {
                    TreeNode * root = new TreeNode(i);
                    root->left = lp;
                    root->right = rp;
                    trees.push_back(root);
                }
            }
        }
        return trees;
    }

    vector<TreeNode*> generateTrees(int n) {
        if (n <= 0) {
            return {};
        }
        return traverse(1, n);
    }
};

void printTree(TreeNode * p) {
    if (p) {
        if (p->left) {
            cout << p->left->val << ",";
        } else {
            cout << "null,";
        }
        if (p->right) {
            cout << p->right->val << ",";
        } else {
            cout << "null,";
        }
        if (p->left) {
            printTree(p->left);
        }
        if (p->right) {
            printTree(p->right);
        }
    }
}
int main() {
    Solution sln;
    vector<TreeNode*> trees = sln.generateTrees(0);
    for (TreeNode* t: trees) {
        if (t) {
            cout << t->val << ",";
            printTree(t);
        }
        cout << "\n";
    }
    return 0;
}
