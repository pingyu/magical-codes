#include <iostream>
#include <vector>

using std::vector;
using std::cout;

#include <algorithm>

class Solution {
public:
    void index_forward(vector<int>& nums, int & index, int end) {
        while (index+1<=end && nums[index+1]==nums[index])
            index++;
    }
    void index_backward(vector<int>& nums, int & index, int begin) {
        while (index-1>=begin && nums[index-1]==nums[index])
            index--;
    }
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> results;
        std::sort(nums.begin(), nums.end());
        int len = nums.size();

        for (int i=0; i<=len-4; i++) {
            if (nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target)
                break;
            if (nums[i] + nums[len-3] + nums[len-2] + nums[len-1] < target)
                continue;

            for (int j=i+1; j<=len-3; j++) {
                if (nums[i] + nums[j] + nums[j+1] + nums[j+2] > target)
                    break;
                if (nums[i] + nums[j] + nums[len-2] + nums[len-1] < target)
                    continue;
                
                int m = j+1, n = len-1;
                while (m < n) {
                    int sum = nums[i] + nums[j] + nums[m] + nums[n];
                    if (sum < target) {
                        index_forward(nums, m, n);
                        m++;
                    } else if (sum > target) {
                        index_backward(nums, n, m);
                        n--;
                    } else {
                        results.emplace_back(vector<int>({nums[i], nums[j], nums[m], nums[n]}));
                        index_forward(nums, m, n);
                        m++;
                        index_backward(nums, n, m);
                        n--;
                    }
                }
                index_forward(nums, j, len-3);
            }
            index_forward(nums, i, len-4);
        }

        return results;
    }
};

struct Case {
    vector<int> nums;
    int target;
};

int main() {
    Case cases[] = {
        {{1, 0, -1, 0, -2, 2}, 0},
        {{0, 0, 0, 0, 0, 0}, 0},
        {{0, 0, 0}, 0},
        {{0, 0, 0, 0}, 0},
        {{-2, -1, 0, 1, 2, 3}, 3},
        {{-2, -1, 0, 1, 2, 3}, 13},
    };

    Solution sln;
    std::ostream_iterator<int> out_it(cout, ",");
    for (auto &c: cases) {
        cout << "CASE: ";
        std::copy(c.nums.begin(), c.nums.end(), out_it);
        cout << ": \n";
        auto sets = sln.fourSum(c.nums, c.target);
        for (auto & ns: sets) {
            std::copy(ns.begin(), ns.end(), out_it);
            cout << "\n";
        }
        cout << "\n";
    }
}
