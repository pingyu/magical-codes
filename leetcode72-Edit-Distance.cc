#include <iostream>

using namespace std;

#include <vector>
#include <algorithm>

const int MAX_INT = 0x7fffffff;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.length(), len2 = word2.length();

        vector<int> v1(len1+1), v2(len1+1);
        auto curr = &v1, prev = &v2;

        (*curr)[0] = 0;

        for (int n=0; n<=len2; n++) {
            auto tmp = curr;
            curr = prev;
            prev = tmp;
            
            for (int m=0; m<=len1; m++) {
                int dist = MAX_INT;
                if (m==0 && n==0)
                    dist = 0;
                if (m >= 1 && n >= 1)
                    dist = (word1[m-1] == word2[n-1]) ? (*prev)[m-1] : (*prev)[m-1] + 1;
                if (m >= 1)
                    dist = std::min(dist, (*curr)[m-1] + 1);
                if (n >= 1)
                    dist = std::min(dist, (*prev)[m] + 1);
                (*curr)[m] = dist;
            }
        }

        return (*curr)[len1];
    }
};

struct Case {
    string word1;
    string word2;
    int expect;
};
int main() {
    Case cases[] = {
        {"horse", "ros", 3},
        {"intention", "execution", 5},
        {"", "", 0},
        {"", "abc", 3},
        {"123", "", 3},
    };
    Solution sln;
    for (auto c: cases) {
        int result = sln.minDistance(c.word1, c.word2);
        cout << c.word1 << " -> " << c.word2 << ": " << c.expect << " --> " << result << "\n";
    }
}
