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
    int lowerBound(vector<int> &nums, int target)
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
    int maximumCount(vector<int> &nums)
    {
        int positiveIndex = lowerBound(nums, 1);
        int negatveIndex = lowerBound(nums, 0) - 1;
        int positiveCount = nums.size() - positiveIndex;
        int negativeCount = negatveIndex + 1;
        return max(positiveCount, negativeCount);
    }
};