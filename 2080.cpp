#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;
class RangeFreqQuery
{
    unordered_map<int, vector<int>> pos;

public:
    RangeFreqQuery(vector<int> &arr)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            pos[arr[i]].push_back(i);
        }
    }

    int query(int left, int right, int value)
    {
        // 不推荐写 a = pos[value]，如果 value 不在 pos 中会插入 value
        auto it = pos.find(value);
        if (it == pos.end())
        {
            return 0;
        }
        auto &a = it->second;
        return ranges::upper_bound(a, right) - ranges::lower_bound(a, left);
    }
};