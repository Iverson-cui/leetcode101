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
    vector<int> answerQueries(vector<int> &nums, vector<int> &queries)
    {
        // Sort nums
        sort(nums.begin(), nums.end());

        // Build tmp: prefix sums excluding current element
        int n = nums.size();
        vector<int> tmp(n, 0);
        tmp[0] = nums[0];
        for (int i = 1; i < n; ++i)
        {
            tmp[i] = tmp[i - 1] + nums[i];
        }

        vector<int> result(queries.size());
        for (int i = 0; i < queries.size(); ++i)
        {
            result[i] = ranges::lower_bound(tmp, queries[i] + 1) - tmp.begin();
        }
        return result;
    }
};