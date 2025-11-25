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
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int len = nums.size();
        int left = 0, right = 0;
        int sum = 0;
        int res = len + 1;
        while (right < len)
        {
            if (sum < target)
            {
                if (right == len)
                {
                    return res == len + 1 ? 0 : res;
                }
                sum += nums[right];
                ++right;
            }
            else
            {
                res = min(res, right - left);
                sum -= nums[left];
                ++left;
            }
        }
        return res == len + 1 ? 0 : res;
    }
};