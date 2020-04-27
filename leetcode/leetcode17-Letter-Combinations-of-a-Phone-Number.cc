#include <iostream>
using namespace std;

#include <vector>
#include <string>

string LETTERS[10] = {
    "", "", // 0, 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz", // 9
};

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> results;

        int len = digits.length();
        if (len <= 0)
            return results;
        
        vector<int> counter(len+1);
        
        while (true) {
            int i;
            string buf(len, '0');
            for (i=0; i<len; i++) {
                buf[i] = LETTERS[digits[i] - '0'][counter[i]];
            }
            results.push_back(std::move(buf));

            i = 0;
            while (i < len) {
                counter[i]++;
                if (counter[i] < LETTERS[digits[i]- '0'].length())
                    break;
                counter[i] = 0;
                i++;
            }
            if (i >= len)
                break;
        }

        return results;
    }
};

int main() {
    string cases[] = {
        "23",
        "9",
        "",
    };
    Solution sln;
    for (auto c: cases) {
        auto results = sln.letterCombinations(c);
        cout << c << ":\n";
        for (auto r: results) {
            cout << r << ", ";
        }
        cout << "\n";
    }
}
