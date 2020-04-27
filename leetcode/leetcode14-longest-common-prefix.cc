#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        auto size = strs.size();
        if (size <= 0) {
            return string("");
        }

        auto str_len = strs[0].length();
        for (auto i=0; i<str_len; i++) {
            auto c = strs[0][i];
            for (auto j=0; j<size; j++) {
                if (i >= strs[j].length() || c != strs[j][i])
                    return strs[0].substr(0, i);
            }
        }
        return strs[0];
    }
};

int main() {
    vector<vector<string> > cases = {
        {"flower","flow","flight"},
        {"dog","racecar","car"},
        {"dog","dog","dog1"},
        {},
        {"dog"},
    };

    Solution sln;
    for (auto&& c: cases) {
        auto result = sln.longestCommonPrefix(c);
        cout << " --> " << result << "\n";
    }
}
