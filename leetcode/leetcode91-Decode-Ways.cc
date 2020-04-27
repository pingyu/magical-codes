#include <iostream>

using namespace std;

#include <vector>

class Solution {
public:
    bool isSingleLegal(char c) {
        return c >= '1' && c <= '9';
    }
    bool isTwoLegal(char c1, char c2) {
        return (c1 == '1') ||
               (c1 == '2' && c2 >= '0' && c2 <= '6');
    }
    int numDecodings(string s) {
        int len = s.length();
        if (len <= 0)
            return 0;
        
        vector<int> ways(len+1);
        ways[0] = 1;

        for (int i=1; i<=len; i++) {
            ways[i] = 0;
            if (isSingleLegal(s[i-1])) {
                ways[i] += ways[i-1];
            }
            if (i-2 >= 0 && isTwoLegal(s[i-2], s[i-1])) {
                ways[i] += ways[i-2];
            }
        }

        return ways[len];
    }
};

struct Case {
    string s;
    int expect;
};
int main() {
    Case cases[] = {
        {"12", 2},
        {"226", 3},
        {"", 0},
        {"0", 0},
        {"30", 0},
    };
    Solution sln;
    for (auto c: cases) {
        auto result = sln.numDecodings(c.s);
        cout << c.s << ": " << c.expect << " --> " << result << "\n";
    }
    return 0;
}
