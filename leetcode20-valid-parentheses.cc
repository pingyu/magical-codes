#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Solution {
public:
    bool isValid(string s) {
        vector<char> stack;
        for (auto c: s) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push_back(c);
            } else {
                if (stack.empty()) {
                    return false;
                }
                auto top = *stack.rbegin();
                if (
                    (c == ')' && top=='(') ||
                    (c == ']' && top=='[') ||
                    (c == '}' && top=='{')
                ) {
                    stack.pop_back();
                } else {
                    return false;
                }
            }
        }
        return stack.empty();
    }
};

struct Case {
    string s;
    bool expect;
};
int main() {
    Case cases[] = {
        {"()", true},
        {"()[]{}", true},
        {"(]", false},
        {"([)]", false},
        {"{[]}", true},
        {"", true},
        {"[", false},
        {")", false}
    };

    Solution sln;
    for (auto c: cases) {
        bool result = sln.isValid(c.s);
        cout << c.s << ": " << c.expect << " --> " << result << "\n";
    }
}
