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
    int lowerBound(vector<int> &nums, long long target)
    {
        int left = 0, right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return left;
    }
    vector<int> successfulPairs(vector<int> &spells, vector<int> &potions, long long success)
    {
        ranges::sort(potions);
        vector<long long> condition(spells.size());
        for (size_t i = 0; i < spells.size(); ++i)
        {
            long long s = spells[i];
            long long val = (ceil(static_cast<double>(success) / s));
            condition[i] = val;
        }
        vector<int> pairs(spells.size());
        for (int i = 0; i < spells.size(); ++i)
        {
            pairs[i] = potions.end() - ranges::lower_bound(potions, condition[i]);
        }
        return pairs;
    }
};

/**
 * 上面的解法直接使用的是ranges::lower_bound。这个函数返回的不是int而是iterator。如果想获取index，可以用it-nums.begin()的方式。获取其后面有多少元素，用nums.end()-it。
 * ranges::lower_bound求的就是大于等于的情况。
 */