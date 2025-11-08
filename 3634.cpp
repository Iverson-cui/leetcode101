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
    int minRemoval(vector<int> &nums, int k)
    {
        sort(nums.begin(), nums.end());
        int len = nums.size();
        int left = 0, right = 0;
        int maxCount = 0;
        for (; right < len; ++right)
        {
            while ((long long)nums[left] * k < nums[right])
            {
                maxCount = max(maxCount, right - left);
                ++left;
            }
        }
        maxCount = max(maxCount, right - left);
        return len - maxCount;
    }
};