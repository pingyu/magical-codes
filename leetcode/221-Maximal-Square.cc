// https://leetcode.com/problems/maximal-square/

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

#include <algorithm>

struct Node {
    int left;
    int top;
    int square_width;
};

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        if (rows <= 0) {
            return 0;
        }
        int cols = matrix[0].size();
        if (cols <= 0) {
            return 0;
        }

        int result = 0;

        vector<vector<Node>> dp(rows);
        for (int r=0; r<rows; r++) {
            dp[r].reserve(cols);

            for (int c=0; c<cols; c++) {
                if ('0' == matrix[r][c]) {
                    dp[r][c] = Node{0,0,0};
                } else {
                    int left = c>0 ? dp[r][c-1].left + 1 : 1;
                    int top = r>0 ? dp[r-1][c].top + 1 : 1;
                    int square_width = c>0 && r>0 ? std::min({dp[r-1][c-1].square_width+1, left, top}) : 1;
                    dp[r][c] = Node{left, top, square_width};

                    result = std::max(result, square_width * square_width);
                }
            }
        }

        return result;
    }
};

struct Case {
    vector<vector<char>> matrix;
    int expect;
};
int main() {
    Case cases[] = {
        {{
            {'1','0','1','0','0'},
            {'1','0','1','1','1'},
            {'1','1','1','1','1'},
            {'1','0','0','1','0'},
        }, 4},
        {{}, 0},
        {{
            {'1'},
        }, 1},
    };
    Solution sln;
    for (auto &c: cases) {
        int res = sln.maximalSquare(c.matrix);
        cout << "res: " << res << ", expect:" << c.expect << "\n";
    }
    return 0;
}
