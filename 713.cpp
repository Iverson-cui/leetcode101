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
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        int len = nums.size();
        int left = 0, right = 0;
        int currentProduct = 1;
        int result = 0;
        for (; right < len; ++right)
        {
            if (currentProduct * nums[right] < k)
            {
                currentProduct *= nums[right];
                // ++right;
                // printf("left: %d, right: %d, result+: %d\n", left, right, right - left + 1);
                result += right - left + 1;
            }
            else if (left == right)
            {
                currentProduct = 1;
                ++left;
            }
            else
            {
                // printf("left: %d, right: %d, product: %d, result+: %d\n", left, right, currentProduct, right - left + 1);
                // result += right - left + 1;
                currentProduct /= nums[left];
                ++left;
                --right;
                // currentProduct = currentProduct / nums[left - 1] * nums[right];
            }
        }
        // printf("final left: %d, right: %d, result+: %d\n", left, right, right - left + 1);
        // result += right - left + 1;
        return result;
    }
};

int main()
{
    Solution solution;
    vector<int> nums = {10, 5, 2, 6};
    int k = 100;
    int result = solution.numSubarrayProductLessThanK(nums, k);
    printf("result: %d\n", result);
    return 0;
}

/**
 *这种写法更加清楚。对于这种求子数组的数目的问题，一般都可以用滑动窗口来解决。思路是固定右端点，寻找所有包含当前右端点，且左端点大于left的数组，其实就是right-left+1个。当right固定时，left需要随时调整到数组符合条件的情况，之后统计这个范围内的子数组数目。
 */

class Solution
{
public:
    int numSubarrayProductLessThanK(vector<int> &nums, int k)
    {
        if (k <= 1)
        {
            return 0;
        }
        int ans = 0, prod = 1, left = 0;
        for (int right = 0; right < nums.size(); right++)
        {
            prod *= nums[right];
            while (prod >= k)
            { // 不满足要求
                prod /= nums[left];
                left++; // 缩小窗口
            }
            // 对于固定的 right，有 right-left+1 个合法的左端点
            ans += right - left + 1;
        }
        return ans;
    }
};