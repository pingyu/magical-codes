#include <iostream>
#include <vector>

using namespace std;

#include <algorithm>
#include <cmath>

class Solution {
public:
    int find(const vector<int>& nums, int begin, int end, int pivot) {
        while (begin < end) {
            int mid = (begin + end) / 2;
            if (nums[mid] == pivot)
                return mid;
            else if (nums[mid] > pivot)
                end = mid - 1;
            else // nums[mid] < pivot
                begin = mid + 1;
        }
        return begin;
    }
    int threeSumClosest(vector<int>& nums, int target) {
        auto len = nums.size();

        int closest = -1;
        int closest_sum = -1;

        std::sort(nums.begin(), nums.end());
        for (int i=0; i<len-2; i++) {
            for (int j=i+1; j<len-1; j++) {
                auto pivot = target - nums[i] - nums[j];
                auto mid = this->find(nums, j+1, len-1, pivot);

                auto diff = std::abs(pivot - nums[mid]);
                auto sum = nums[i] + nums[j] + nums[mid];
                if (mid>j+1 && std::abs(pivot - nums[mid-1]) < diff) {
                    diff = std::abs(pivot - nums[mid-1]);
                    sum = nums[i] + nums[j] + nums[mid-1];
                }
                if (mid<len-1 && std::abs(pivot - nums[mid+1]) < diff) {
                    diff = std::abs(pivot - nums[mid+1]);
                    sum = nums[i] + nums[j] + nums[mid+1];
                }
                
                if (closest==-1 || diff < closest) {
                    closest = diff;
                    closest_sum = sum;
                }
            }
        }
        return closest_sum;
    }
};

struct Case {
    vector<int> v;
    int target;
    int expect;
};
int main() {
    Case cases[] = {
        {{-1, 2, 1, -4}, 1, 2},
        {{-1, 2, 1, 1, -4}, 1, 1},
        {{-1, 2, 10}, 1, 11},
    };

    Solution sln;
    for (auto c: cases) {
        auto result = sln.threeSumClosest(c.v, c.target);
        cout << c.v[0] << ", " << c.target << ": " << c.expect << " --> " << result << "\n";
    }

}