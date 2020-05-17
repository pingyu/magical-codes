// https://leetcode.com/problems/divide-two-integers/

#include <iostream>
#include <numeric>
using std::cout;

const int MIN_INT = 0x80000000;
const int MAX_INT = 0x7fffffff;
const int OVER_FLOW = MAX_INT;

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (MIN_INT==dividend && -1==divisor) {
            return OVER_FLOW;
        }
        if (MIN_INT==divisor) {
            if (MIN_INT==dividend) {
                return 1;
            }
            return 0;
        }

        int quotient = 0;
        int sum = 0;
        bool minus = false;
        if (dividend >= 0) {
            if (divisor < 0) {
                minus = true;
                divisor = -divisor;
            }
            int acc = int((unsigned int)sum + (unsigned int)divisor);
            while ( acc <= dividend && acc > sum ) {
                quotient++;
                sum += divisor;
                acc = int((unsigned int)sum + (unsigned int)divisor);
            }
        } else {
            if (divisor > 0) {
                minus = true;
                divisor = -divisor;
            }
            int acc = int((unsigned int)sum + (unsigned int)divisor);
            while ( acc >= dividend && acc < sum ) {
                quotient++;
                sum += divisor;
                acc = int((unsigned int)sum + (unsigned int)divisor);
            }
        }

        if (minus) {
            quotient = -quotient;
        }
        return quotient;
    }
};

struct Case {
    int dividend;
    int divisor;
    int expect;
};
int main() {
    Case cases[] {
        {10, 3, 3},
        {7, -3, -2},
        {2147483647, 1, 2147483647},
        {std::numeric_limits<int>::max(), 1, std::numeric_limits<int>::max()},
        {std::numeric_limits<int>::min(), 1, std::numeric_limits<int>::min()},
        {std::numeric_limits<int>::max(), -1, -std::numeric_limits<int>::max()},
        {std::numeric_limits<int>::min(), -1, std::numeric_limits<int>::max()},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), 1},
        {std::numeric_limits<int>::max()-1, std::numeric_limits<int>::max(), 0},
        {std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), 1},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), 0},
    };

    Solution sln;
    for (auto&c: cases) {
        int res = sln.divide(c.dividend, c.divisor);
        cout << "dividend: " << c.dividend << ", divisor:" << c.divisor << ", res:" << res << ", expect:" << c.expect << "\n";
    }
    return 0;
}
