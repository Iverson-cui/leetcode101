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
    int longestOnes(vector<int> &nums, int k)
    {
        int len = nums.size();
        int left = 0, right = 0;
        int maxLen = 0;
        int count = 0;
        for (; right < len; ++right)
        {
            if ((nums[right] == 0) && (count < k))
            {
                ++count;
            }
            else if (nums[right] == 0 && count == k)
            {
                while (nums[left] != 0)
                {
                    ++left;
                }
                ++left;
            }
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};

/**
 * 如下是一种很妙的写法。
 */
class Solution
{
public:
    int longestOnes(vector<int> &nums, int k)
    {
        int ans = 0, left = 0, cnt0 = 0;
        for (int right = 0; right < nums.size(); right++)
        {
            cnt0 += 1 - nums[right]; // 0 变成 1，用来统计 cnt0
            while (cnt0 > k)
            {
                cnt0 -= 1 - nums[left];
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};
