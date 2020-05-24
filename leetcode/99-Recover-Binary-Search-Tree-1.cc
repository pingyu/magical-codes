// https://leetcode.com/problems/recover-binary-search-tree/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
protected:
    TreeNode * m_nodeLhs;
    bool m_phaseOne;
    bool m_phaseTwo;

    TreeNode * traverse(TreeNode* root, TreeNode * prev) {
        if (root->left) {
            prev = traverse(root->left, prev);
            if (!prev) {
                return nullptr;
            }
        }

        if (m_phaseOne) {
            if (prev && prev->val > root->val) {
                m_nodeLhs = prev;
                m_phaseOne = false;
                m_phaseTwo = true;
            }
        } else if (m_phaseTwo) {
            if (m_nodeLhs->val < root->val) {
                int tmp = m_nodeLhs->val;
                m_nodeLhs->val = prev->val;
                prev->val = tmp;
                m_phaseTwo = false;
                return nullptr;
            }
        }
        
        if (root->right) {
            return traverse(root->right, root);
        }
        return root;
    }

public:
    void recoverTree(TreeNode* root) {
        m_nodeLhs = nullptr;
        m_phaseOne = true;
        m_phaseTwo = false;
        TreeNode * prev = traverse(root, nullptr);
        if (m_phaseTwo) {
            int tmp = m_nodeLhs->val;
            m_nodeLhs->val = prev->val;
            prev->val = tmp;
        }
    }
};

int main() {
    TreeNode * cases[] = {
        new TreeNode(1, new TreeNode(3, nullptr, new TreeNode(2)), nullptr),
        new TreeNode(3, new TreeNode(1), new TreeNode(4, new TreeNode(2), nullptr)),
    };
    Solution sln;
    for (auto t: cases) {
        sln.recoverTree(t);
    }
    return 0;
}
