#include <iostream>
#include <vector>


#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

class Solution {
public:
    struct Value {
        int a;
        int b;
        int c;
        Value() {
            a = b = c = 0;
        }
        Value(int a_, int b_, int c_) {
            a = a_;
            b = b_;
            c = c_;
            if (a > b) swap(a, b);
            if (b > c) swap(b, c);
            if (a > b) swap(a, b);
        }
        bool operator== (const Value & rhs) const {
            if (this->a == rhs.a) {
                if (this->b == rhs.b) {
                    return this->c == rhs.c;
                }
                return this->b == rhs.b;
            }
            return this->a == rhs.a;
        }
        void swap(int& m, int& n) {
            auto t = m;
            m = n;
            n = t;
        }
    };
    struct MyHash {
        std::size_t operator()(Value const& v) const noexcept
        {
            std::size_t h1 = std::hash<int>{}(v.a);
            std::size_t h2 = std::hash<int>{}(v.b);
            std::size_t h3 = std::hash<int>{}(v.c);
            return (h1 ^ (h2 << 1)) ^ (h3 << 1); // or use boost::hash_combine (see Discussion)
        }
    };
    vector<vector<int>> threeSum(vector<int>& nums) {
        unordered_set<Value, MyHash> result;
        unordered_map<int, int> index;

        for (int i=0; i<nums.size(); i++) {
            index[nums[i]] = i;
        }

        for (int i=1; i<nums.size(); i++) {
            for (int j=0; j<i; j++) {
                auto it = index.find(-nums[i]-nums[j]);
                if (index.end() != it && it->second > i) {
                    result.emplace(nums[i], nums[j], -nums[i]-nums[j]);
                    //cout << "{" << j << "," << i << "," << it->second << "}\n";
                }
            }
        }

        vector<vector<int>> output;
        for (auto&& [a, b, c]: result) {
            vector<int> v = {a, b, c};
            output.emplace_back(std::move(v));
        }
        return output;
    }
};

int main() {
    Solution sln;
    vector<vector<int>> cases = {
        {-1, 0, 1, 2, -1, -4},
        {},
        {0},
        {-1, 1},
        {-1, -1, -1, 0, 0, 0, 1, 1, 1},
    };
    for (auto&& c: cases) {
        auto&& result = sln.threeSum(c);
        cout << "RESULT: ";
        for (auto& v: result) {
            for (auto& i: v) {
                cout << i << ",";
            }
            cout << " || ";
        }
        cout << "\n";
    }
}
