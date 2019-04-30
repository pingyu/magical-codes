#include <iostream>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        auto len = s.length();
        auto num = 0;
        for (auto i=0; i<len; i++) {
            switch (s[i]) {
            case 'I':
                if (i+1<len && s[i+1]=='V') {
                    num += 4;
                    i++;
                } else if (i+1<len && s[i+1]=='X') {
                    num += 9;
                    i++;
                } else {
                    num += 1;
                }
                break;

            case 'V':
                num += 5;
                break;

            case 'X':
                if (i+1<len && s[i+1]=='L') {
                    num += 40;
                    i++;
                } else if (i+1<len && s[i+1]=='C') {
                    num += 90;
                    i++;
                } else {
                    num += 10;
                }
                break;
            
            case 'L':
                num += 50;
                break;
            
            case 'C':
                if (i+1<len && s[i+1]=='D') {
                    num += 400;
                    i++;
                } else if (i+1<len && s[i+1]=='M') {
                    num += 900;
                    i++;
                } else {
                    num += 100;
                }
                break;
            
            case 'D':
                num += 500;
                break;
            
            case 'M':
                num += 1000;
                break;
            }
        }
        return num;
    }
};

struct Case {
    string input;
    int expected;
};

int main() {
    Case cases[] = {
        {"III", 3},
        {"IV", 4},
        {"IX", 9},
        {"LVIII", 58},
        {"MCMXCIV", 1994},
        {"", 0}
    };

    Solution sln;
    for (auto&& c: cases) {
        auto output = sln.romanToInt(c.input);
        cout << "input: " << c.input << " expect: " << c.expected << " output: " << output << "\n";
    }

    return 0;
}
