#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        auto rows = grid.size();
        if (rows <= 0)
            return 0;
        auto cols = grid[0].size();

        for (auto i=0; i<rows; i++) {
            for (auto j=0; j<cols; j++) {
                auto min = -1;
                if (i - 1 >= 0) {
                    min = grid[i-1][j];
                }
                if (j - 1 >= 0) {
                    if (min < 0 || min > grid[i][j-1])
                        min = grid[i][j-1];
                }
                if (min > 0)
                    grid[i][j] = grid[i][j] + min;
            }
        }

        return grid[rows-1][cols-1];
    }
};

int main() {
    vector<vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    Solution sln;
    cout << sln.minPathSum(grid) << "\n";
}
