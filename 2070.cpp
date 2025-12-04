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

class Solution
{
public:
    vector<int> maximumBeauty(vector<vector<int>> &items, vector<int> &queries)
    {
        sort(items.begin(), items.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[0] < b[0]; });
        // Extract columns
        vector<int> firsts, seconds;
        firsts.reserve(items.size());
        seconds.reserve(items.size());
        for (const auto &it : items)
        {
            firsts.push_back(it[0]);
            seconds.push_back(it[1]);
        }
        for (size_t i = 1; i < seconds.size(); ++i)
        {
            seconds[i] = max(seconds[i], seconds[i - 1]);
        }
        for (int &q : queries)
        {
            int index = ranges::lower_bound(firsts, q + 1) - firsts.begin();
            if (index == 0)
            {
                q = 0;
            }
            else
            {
                q = seconds[index - 1];
            }
        }
        return queries;
    }
};