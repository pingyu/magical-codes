#include <bits/stdc++.h>

using std::cout;
using std::cin;
using std::vector;

#include <algorithm>
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int N = prices.size();
        if (N <= 0) {
            return 0;
        }

        int minn = prices[0];
        int maxx = 0;

        for (int i=1; i<N; i++) {
            if (prices[i] < minn) {
                minn = prices[i];
            } else {
                maxx = std::max(maxx, prices[i] - minn);
            }
        }
        
        return maxx;
    }
};

struct Case {
    vector<int> input;
    int expect;
};

int main() {
    Case cases[] = {
        {{7,1,5,3,6,4}, 5},
        {{7,6,4,3,1}, 0},
        {{}, 0},
        {{2}, 0},
    };
    Solution sln;
    for (auto& c: cases) {
        int max = sln.maxProfit(c.input);
        cout << "max: " << max << ", expect:" << c.expect << "\n";
    }
    return 0;
}
