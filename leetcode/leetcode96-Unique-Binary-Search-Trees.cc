#include <bits/stdc++.h>
using std::cout;
using std::cin;


class Solution {
public:
    int numTrees(int n) {
        std::vector<int> vec(n+1);

        vec[1] = 1;
        for (int i=2; i<=n; i++) {
            vec[i] = 2 * vec[i - 1];
            if (i >= 3) {
                for (int j=1; j<i - 1; j++) {
                    vec[i] += vec[j] * vec[i - 1 - j];
                }
            }
        }

        return vec[n];
    }
};

struct Case {
    int n;
    int expect;
};
int main() {
    Case cases[] = {
        {3, 5},
        {0, 0},
        {1, 1},
        {2, 2},
        {4, 4},
    };
    Solution sln;
    for (auto& c: cases) {
        int r = sln.numTrees(c.n);
        cout << "n: " << c.n << ", r: " << r << ", expect: " << c.expect << "\n";
    }
    return 0;
}