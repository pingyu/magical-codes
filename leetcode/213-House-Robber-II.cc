// https://leetcode.com/problems/house-robber-ii/

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
        if (length <= 0) {
            return 0;
        }
        if (length == 1) {
            return nums[0];
        }

        vector<int> dp0(length+2), dp1(length+2);
        dp0[2] = 0;
        dp1[2] = nums[0];

        for (int i=1; i<length; i++) {
            int ii = i + 2;
            dp0[ii] = std::max(dp0[ii-2]+nums[i], dp0[ii-1]);
            if (i < length-1) {
                dp1[ii] = std::max(dp1[ii-2]+nums[i], dp1[ii-1]);
            } else {
                dp1[ii] = std::max(dp1[ii-2], dp1[ii-1]);
            }
        }
        return std::max(dp0[2+length-1], dp1[2+length-1]);
    }
};

struct Case {
    vector<int> input;
    int expect;
};
int main() {
    Case cases[] = {
        {{2,3,2}, 3},
        {{1,2,3,1}, 4},
        {{}, 0},
        {{1}, 1},
        {{1,2}, 2},
        {{1,1,3,6,7,10,7,1,8,5,9,1,4,4,3}, 41},
    };
    Solution sln;
    for (auto &c: cases) {
        int res = sln.rob(c.input);
        cout << "res: " << res << " , expect: " << c.expect << "\n";
    }
    return 0;
}
