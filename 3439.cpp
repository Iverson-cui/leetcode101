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
    int maxSum(vector<int> &nums, int size)
    {
        int len = nums.size();
        if (size >= len)
            return accumulate(nums.begin(), nums.end(), 0);
        int max_sum = 0;
        int current_sum = 0;
        for (int i = 0; i <= len - size; ++i)
        {
            if (i == 0)
            {
                current_sum = accumulate(nums.begin(), nums.begin() + size, 0);
                max_sum = current_sum;
            }
            else
            {
                current_sum = current_sum + nums[i + size - 1] - nums[i - 1];
                max_sum = max(max_sum, current_sum);
            }
        }
        return max_sum;
    }
    int maxFreeTime(int eventTime, int k, vector<int> &startTime, vector<int> &endTime)
    {
        vector<int> intervals;
        intervals.push_back(startTime[0]);
        int len = startTime.size();
        for (int i = 0; i < len - 1; ++i)
        {
            intervals.push_back(startTime[i + 1] - endTime[i]);
        }
        intervals.push_back(eventTime - endTime[len - 1]);
        return maxSum(intervals, k + 1);
    }
};