#include <iostream>
#include <vector>

using std::vector;
using std::cout;

#include <map>
#include <set>
#include <iterator>
#include <algorithm>
#include <numeric>

class Solution {
public:
    using NumsMap = std::map<int, int>;
    using NumsMapIter = NumsMap::iterator;
    //using ResultSet = std::set<vector<int>>;
    using ResultSet = vector<vector<int>>;

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        NumsMap nums_map;

        for (auto n: nums) {
            int & count = nums_map[n];
            if (count <= 3)
                count++;
        }

        ResultSet result_set;
        vector<int> result;
        calc(target, nums_map, nums_map.begin(), 0, result, result_set);

        //vector<vector<int>> results;
        //std::copy(result_set.begin(), result_set.end(), std::back_inserter(results));
        //return results;
        return result_set;
    }

    void calc(int target, NumsMap & nums_map, NumsMapIter it, int index_in_bucket, vector<int> & result, ResultSet & result_set) {
        if (nums_map.end() == it)
            return;

        int num = it->first;
        int count = it->second;

        if (result.size() == 3) {
            int left = target - std::accumulate(result.begin(), result.end(), 0);
            if (left == num) {
                result.push_back(num);
                //result_set.insert(result);
                result_set.push_back(result);
                result.pop_back();
            } else if (left > num) {
                NumsMapIter it_left = nums_map.find(left);
                if (nums_map.end() != it_left) {
                    result.push_back(it_left->first);
                    //result_set.insert(result);
                    result_set.push_back(result);
                    result.pop_back();
                }
            }
            return;
        }

        // pick 0
        calc(target, nums_map, std::next(it), 0, result, result_set);

        // pick 1 ~ min(count, 4 - result.size())
        int max_c = std::min(count, int(4 - result.size()));
        for (int c=1; c<=max_c; c++) {
            result.push_back(num);
            if (result.size() == 4) {
                if (std::accumulate(result.begin(), result.end(), 0) == target) {
                    //result_set.insert(result);
                    result_set.push_back(result);
                }
            } else {
                calc(target, nums_map, std::next(it), 0, result, result_set);
            }
        }
        for (int c=1; c<=max_c; c++) {
            result.pop_back();
        }        
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
