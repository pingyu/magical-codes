// https://leetcode.com/problems/generate-parentheses/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::cout;
using std::vector;
using std::string;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        int N = n + n;
        vector<string> result;
        string s;
        s.resize(N);
        solve(s, 0, 0, result, N);
        return result;
    }

    void solve(string &s, int index, int sum, vector<string> &result, int n) {
        if (index == n) {
            if (0 == sum) {
                result.push_back(s);
            }
            return;
        } 
        if (sum < n - index) {
            s[index] = '(';
            solve(s, index+1, sum+1, result, n);
        }
        if (sum > 0) {
            s[index] = ')';
            solve(s, index+1, sum-1, result, n);
        }
    }
};

struct Case {
    int n;
};
int main() {
    Case cases[] = {
        {3},
        {4},
    };
    Solution sln;
    for (auto& c: cases) {
        auto res = sln.generateParenthesis(c.n);
        for (auto&s: res) {
            cout << s << "\n";
        }
        cout << "---------------------\n";
    }

    return 0;
}
