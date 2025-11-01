#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
public:
    double calAverage(vector<int> &nums, int start, int k)
    {
        int sum = 0;
        for (int i = start; i < start + k; i++)
        {
            sum += nums[i];
        }
        return (double)sum / k;
    }
    double findMaxAverage(vector<int> &nums, int k)
    {
        int currSum = 0;
        int maxSum = 0;
        int start = 0;
        int end = k - 1;
        int len = nums.size();
        for (int i = 0; i < k; ++i)
        {
            currSum += nums[i];
        }
        maxSum = currSum;
        while (end < len - 1)
        {
            currSum = currSum - nums[start] + nums[end + 1];
            if (nums[end + 1] > nums[start])
            {
                // currSum = currSum - nums[start] + nums[end + 1];
                maxSum = max(maxSum, currSum);
                start++;
                end++;
            }
            else
            {
                start++;
                end++;
            }
        }
        return (double)maxSum / k;
    }
};