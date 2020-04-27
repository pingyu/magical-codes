#include <iostream>
#include <vector>
using namespace std;

#include <algorithm>

class Solution {
public:
    struct Point {
        int i;
        int j;
    };
    struct Item {
        Point left;
        Point top;
        Point diagonal;
    };
    int calc_area(const Item & itm, int i, int j) {
        return std::max({
            (i - itm.diagonal.i + 1) * (j - itm.diagonal.j + 1),
            (i - itm.top.i + 1),
            (j - itm.left.j + 1)
        });
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int height = matrix.size();
        if (height <= 0)
            return 0;
        
        int width = matrix[0].size();
        if (width <= 0)
            return 0;
        
        vector<Item> v1(width), v2(width);
        auto curr = &v1, prev = &v2;

        int max_area = 1;
        for (int i=0; i<height; i++) {
            for (int j=0; j<width; j++) {
                auto tmp = curr;
                curr = prev;
                prev = tmp;
                
                if (matrix[i][j] != '1')
                    continue;
                
                Item itm;
                // top
                if (i>0 && matrix[i-1][j]=='1') {
                    itm.top = (*prev)[j].top;
                } else {
                    itm.top = Point{i, j};
                }
                // left
                if (j>0 && matrix[i][j-1]=='1') {
                    itm.left = (*curr)[j-1].left;
                } else {
                    itm.left = Point{i, j};
                }
                // diagonal
                if (i>0 && j>0 && matrix[i-1][j-1]=='1') {
                    itm.diagonal = Point{
                        std::min((*prev)[j-1].diagonal.i, itm.top.i),
                        std::min((*prev)[j-1].diagonal.j, itm.left.j)
                    };
                } else {
                    itm.diagonal = Point{i, j};
                }

                max_area = std::max(max_area, calc_area(itm, i, j));
                (*curr)[j] = std::move(itm);
            }
        }

        return max_area;
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
        }, 6},

        {{
            {'1','0','1','0','0'},
            {'1','0','1','1','1'},
            {'1','1','1','1','1'},
            {'1','0','0','1','0'},
        }, 6},
    };
    Solution sln;
    for (auto c: cases) {
        int result = sln.maximalRectangle(c.matrix);
        cout << c.expect << " --> " << result << "\n";
    }

    return 0;
}
