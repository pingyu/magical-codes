// https://leetcode.com/problems/house-robber/

#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::cout;

#include <algorithm>
class Solution {
public:
    int rob(vector<int>& nums) {
        int length = nums.size();
        if (length <= 0)
            return 0;

        vector<int> dp(length);

        for (int i=0; i<length; i++) {
            int m = i-2 >= 0 ? dp[i-2] : 0;
            int n = i-1 >= 0 ? dp[i-1] : 0;
            dp[i] = std::max(m+nums[i], n);
        }
        return dp[length-1];
    }
};

struct Case {
    vector<int> input;
    int expect;
};
int main() {
    Case cases[] = {
        {{1,2,3,1}, 4},
        {{2,7,9,3,1}, 12},
        {{5, 1, 1, 5}, 10},
        {{}, 0},
        {{1}, 1},
        {{1,2}, 2},
    };
    Solution sln;
    for (auto &c: cases) {
        int res = sln.rob(c.input);
        cout << "res: " << res << " , expect: " << c.expect << "\n";
    }
    return 0;
}
