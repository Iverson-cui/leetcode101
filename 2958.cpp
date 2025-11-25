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
    int maxSubarrayLength(std::vector<int> &nums, int k)
    {
        int len = nums.size();
        int left = 0, right = 0;
        int maxLen = 0;
        // int maxNum = ranges::max(nums);
        unordered_map<int, int> count;
        for (; right < len; ++right)
        {
            ++count[nums[right]];
            while (count[nums[right]] > k)
            {
                --count[nums[left]];
                ++left;
            }
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};

/**
 * 在这里，ranges::max(nums) 用于找到数组 nums 中的最大值。如果用这个最大值作为vector的size，比如[1,1000]，会创建1000长度的vector，浪费大量空间。这种情况下还是unordered_map更好一些。
 */
