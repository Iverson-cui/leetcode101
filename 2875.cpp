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
    int minSizeSubarray(vector<int> &nums, int target)
    {
        int iterCount = 0;
        long long sumNums = accumulate(nums.begin(), nums.end(), 0LL);
        // printf("sumNums=%lld\n", sumNums);
        if (sumNums < target)
        {
            iterCount = target / sumNums;
            target = target % sumNums;

            // printf("iterCount=%d\n", 39 / sumNums);
            // printf("target=%d, iterCount=%d\n", target, iterCount);
        }
        int len = nums.size();
        int left = 0, right = 0;
        long long currentSum = 0;
        long long result = INT64_MAX;

        for (; right < 2 * len; ++right)
        {
            currentSum += nums[right % len];
            while (currentSum > target)
            {
                currentSum -= nums[left % len];
                ++left;
            }
            if (currentSum == target)
            {
                result = min(result, (long long)(right - left + 1) + iterCount * len);
                // result = min(result, (right - left + 1));
            }
            // if ((left == 0) && (right == 2 * len - 1))
            // {
            //     right = 0;
            //     left = 0;
            //     iterCount++;
            // }
        }
        return result == INT64_MAX ? -1 : result;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {2, 1, 5, 7, 7, 1, 6, 3};
    int target = 39;
    int result = sol.minSizeSubarray(nums, target);
    printf("Result: %d\n", result);
    return 0;
}