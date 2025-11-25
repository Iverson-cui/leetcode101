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
    int maximumBeauty(vector<int> &nums, int k)
    {
        sort(nums.begin(), nums.end());
        int left = 0, right = 0;
        int maxLen = 1;
        int len = nums.size();
        for (; right < len; ++right)
        {
            while (nums[left] + 2 * k < nums[right])
            {
                ++left;
            }
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};