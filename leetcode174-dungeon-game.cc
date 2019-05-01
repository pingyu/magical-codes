//#include <iostream>
#include <vector>

using namespace std;

#include <map>
#include <algorithm>

class Solution {
public:
    using NodeMap = map<int, int, std::greater<int>>;
    void insertNode(NodeMap & m, int least, int current) {
        auto it = m.find(least);
        if (it==m.end()) {
            m[least] = current;
        }
        else if (it->second < current) {
            it->second = current;
        }
    }
    void mergeNode(NodeMap & m, const NodeMap & from, int damage) {
        for (auto&& [least, current]: from) {
            auto currentNew = current + damage;
            auto leastNew = currentNew < least ? currentNew : least;
            insertNode(m, leastNew, currentNew);
        }
    }
    void compressNode(NodeMap & m) {
        auto prevCurrent = 0;
        for (auto it=m.begin(); it!=m.end();) {
            //cout << it->first << " -> " << it->second << "\n";
            if (it == m.begin()) {
                prevCurrent = it++->second;
                continue;
            }
            if (it->second <= prevCurrent) {
                m.erase(it++);
            } else {
                prevCurrent = it++->second;
            }
        }
    }
    void printNode(const NodeMap & m) {
        for (auto&& [least, current]: m) {
            //cout << "[" << least << ":" << current << "] ";
        }
    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        auto rows = dungeon.size();
        if (rows <= 0)
            return 0;
        auto cols = dungeon[0].size();

        vector<NodeMap> v0, v1;
        v0.resize(cols);
        v1.resize(cols);

        auto *curr = &v0;
        auto *prev = &v1;
        for (int i=0; i<rows; i++) {
            for (int j=0; j<cols; j++) {
                auto&& node = (*curr)[j];
                auto damage = dungeon[i][j];

                //cout << "(" << i << "," << j << "): --> " << damage << "\n";

                if (i==0 && j==0) {
                    insertNode(node, damage, damage);
                }
                else {
                    node.clear();
                    if (i-1 >= 0) {
                        mergeNode(node, (*prev)[j], damage);
                        //printNode(node);
                        //cout << "\n";
                    }
                    if (j-1 >= 0) {
                        mergeNode(node, (*curr)[j-1], damage);
                        //printNode(node);
                        //cout << "\n";
                    }
                    compressNode(node);
                }

                //printNode(node);
                //cout << "\n\n";
            }
            auto tmp = prev;
            prev = curr;
            curr = tmp;
        }

        auto least = (*prev)[cols-1].begin()->first;
        if (least < 0)
            return -least + 1;
        else
            return 1;
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
        //cout << sln.calculateMinimumHP(c) << "\n";
        //cout << "---------------------------------\n\n";
    }
}
