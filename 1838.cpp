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
    int maxFrequency(vector<int> &nums, int k)
    {
        ranges::sort(nums);
        int left = 0;
        long long totalDiff = 0;
        int maxFreq = 1;
        int len = nums.size();
        if (len == 1)
        {
            return 1;
        }
        for (int right = 1; right < len; ++right)
        {
            printf("left: %d, right: %d, totalDiff: %d\n", left, right, totalDiff);
            if (right == 1)
            {
                totalDiff = nums[right] - nums[right - 1];
            }
            else
            {
                totalDiff += (right - left) * 1LL * (nums[right] - nums[right - 1]);
                printf("after add, totalDiff: %lld\n", totalDiff);
            }
            while (totalDiff > k)
            {
                printf("before remove, totalDiff: %lld\n", totalDiff);
                totalDiff -= (nums[right] - nums[left]);
                ++left;
                printf("after remove, totalDiff: %lld\n", totalDiff);
            }
            printf("current length: %d\n", right - left + 1);
            maxFreq = max(maxFreq, right - left + 1);
        }
        return maxFreq;
    }
};

int main(void)
{
    Solution solution;
    vector<int> nums = {1, 4, 8, 13};
    int k = 5;
    int result = solution.maxFrequency(nums, k);
    cout << result << endl;
    return 0;
}

/**
 * 可以给一个乘式乘1LL，避免int溢出
 */