#include <iostream>

using namespace std;

#include <cmath>

class Solution {
public:
    int climbStairs(int n) {
        double sqrt5 = std::pow(5.0, 0.5);
        return int( 1.0 / sqrt5 * ( std::pow((1+sqrt5)/2, n+1) - std::pow((1-sqrt5)/2, n+1) ) );
    }
};

struct Case {
    int n;
    int expect;
};
int main() {
    Case cases[] = {
        {2, 2},
        {3, 3},
        {1, 1},
        {6, 13},
    };
    Solution sln;
    for (auto c: cases) {
        int result = sln.climbStairs(c.n);
        cout << c.n << ": " << c.expect << " --> " << result << "\n";
    }
    return 0;
}