// https://leetcode.com/problems/word-break/

#include <bits/stdc++.h>

using std::cout;
using std::cin;
using std::string;
using std::vector;

class Solution {
public:
    struct Node {
        std::unordered_map<char, Node*> children;
    };
    Node trie;
    void makeTrie(const vector<string>& wordDict) {
        for (auto& s: wordDict) {
            Node *pp = &trie;
            int len = s.length();
            for (int i=len-1; i>=0; i--) {
                char c = s[i];
                Node *p = pp->children[c];
                if (nullptr == p) {
                    p = new Node;
                    pp->children[c] = p;
                }
                pp = p;
            }
            pp->children['\0'] = nullptr;
        }
    }
    void printTrie(Node * p) {
        for (auto& x: p->children) {
            if ('\0' == x.first) {
                cout << "-";
            } else {
                cout << x.first;
                printTrie(x.second);
            }
        }
    }
    void cleanTrie(Node * p) {
        for (auto& x: p->children) {
            if (nullptr != x.second) {
                cleanTrie(x.second);
                delete x.second;
            }
        }
        p->children.clear();
    }

    bool walk(const string& s, int index, Node * p, vector<bool>& mark) {
        auto it = p->children.find('\0');
        if (it != p->children.end()) {
            if (index < 0) {
                return true;
            }
            if (mark[index]) {
                return true;
            }
        }

        if (index < 0) {
            return false;
        }

        char c = s[index];
        it = p->children.find(c);
        if (it != p->children.end()) {
            return walk(s, index-1, it->second, mark);
        }
        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        makeTrie(wordDict);
        // printTrie(&trie);

        int N = s.length();
        vector<bool> mark(N);
        for (int i=0; i<N; i++) {
            if (walk(s, i, &trie, mark)) {
                mark[i] = true;
            }
        }

        cleanTrie(&trie);
        return mark[N-1];
    }
};


struct Case {
    string s;
    vector<string> wordDict;
    bool expect;
};
int main() {
    Case cases[] {
        {
            "leetcode",
            {"leet", "code"},
            true
        },
        {
            "applepenapple",
            {"apple", "pen"},
            true
        },
        {
            "catsandog",
            {"cats", "dog", "sand", "and", "cat"},
            false
        },
        {
            "n",
            {"a"},
            false
        },
        {
            "n",
            {"n"},
            true
        }
    };
    Solution sln;
    for (auto& c: cases) {
        bool res = sln.wordBreak(c.s, c.wordDict);
        cout << "res:" << res << ", expect:" << c.expect << "\n";
    }
    return 0;
}
