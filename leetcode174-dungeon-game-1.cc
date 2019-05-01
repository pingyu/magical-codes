#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static constexpr int MAX32 = 0x7fffffff;

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        auto rows = dungeon.size();
        if (rows <= 0)
            return 1;
        auto cols = dungeon[0].size();
        if (cols <=0)
            return 1;

        vector<int> v0(cols+1, MAX32), v1(cols+1, MAX32);
        auto *curr = &v0;
        auto *next = &v1;

        (*next)[cols-1] = 1;
        for (int i=rows-1; i>=0; i--) {
            for (int j=cols-1; j>=0; j--) {
                auto &now = (*curr)[j];
                auto right = (*curr)[j+1];
                auto down = (*next)[j];

                now = (right < down ? right : down) - dungeon[i][j];
                if (now <= 0)
                    now = 1;
            }
            auto tmp = curr;
            curr = next;
            next = tmp;
        }

        return (*next)[0];
    }
};

int main() {
    vector<vector<int>> cases[] = {
        {{-2, -3, 3},
        {-5, -10, 1},
        {10, 30, -5}},

        {{2, 3, 3},
        {5, 10, 1},
        {10, 30, -5}},
    };

    Solution sln;

    for (auto&& c : cases) {
        cout << sln.calculateMinimumHP(c) << "\n";
        cout << "---------------------------------\n\n";
    }
}
