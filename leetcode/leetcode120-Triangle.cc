
#include <bits/stdc++.h>

using std::cout;
using std::cin;
using std::vector;

#include <algorithm>
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int N = triangle.size();
        if (0 == N) {
            return 0;
        }

        vector<int> sum(N);
        sum[0] = triangle[0][0];

        for (int i=1; i<N; i++) {
            sum[i] = sum[i-1] + triangle[i][i];
            for (int j=i-1; j>0; j--) {
                sum[j] = std::min(sum[j], sum[j-1]) + triangle[i][j];
            }
            sum[0] = sum[0] + triangle[i][0];
        }

        return *std::min_element(sum.begin(), sum.end());
    }
};


struct Case {
    vector<vector<int>> triangle;
    int expect;
};

int main() {
    Case cases[] = {
        {
            {
                {2},
                {3, 4},
                {6, 5, 7},
                {4, 1, 8, 3},
            }, 11
        },
        {
            {}, 0
        },
        {
            {
                {2}
            }, 2
        },
    };
    Solution sln;
    for (auto& c: cases) {
        int sum = sln.minimumTotal(c.triangle);
        cout << "sum:" << sum << ", expect:" << c.expect << "\n";
    }
    return 0;
}
