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
    // sum>=goal sliding window function
    int slidingWindow(vector<int> &nums, int goal)
    {
        int len = nums.size();
        int sum = 0;
        int left = 0, right = 0;
        int result = 0;
        for (; right < len; ++right)
        {
            sum += nums[right];
            while (sum >= goal)
            {
                result += (len - right);
                sum -= nums[left];
                if (left == right)
                {
                    ++left;
                    break;
                }
                ++left;
            }
        }
        return result;
    }
    int numSubarraysWithSum(vector<int> &nums, int goal)
    {
        return slidingWindow(nums, goal) - slidingWindow(nums, goal + 1);
    }
};

/**
 * 前面讲的统计子字符串的数目的问题要么是越大越合法，要么是越小越合法。如果对于本题这种要求字符串长度严格等于k的情况，可以转化为2个越大越合法问题。即对于sum=k的要求，我们求sum>=k+1 - sum>=k的值即可。
 */