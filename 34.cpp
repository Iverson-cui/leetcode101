#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

vector<int> searchRange(vector<int> &nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    int have = 0;
    int mid;
    while (left <= right)
    {

        mid = left + (right - left) / 2;
        // if mid is the wanted target
        if (nums[mid] == target)
        {
            have = 1;
            break;
        }
        // if mid is less than target
        else if (nums[mid] < target)
        {
            left = mid + 1;
        }
        // if mid is greater than target
        else
        {
            right = mid - 1;
        }
    }
    if (have == 0)
    {
        return {-1, -1};
    }
    else
    {
        int left_bound = mid;
        int right_bound = mid;
        while (left_bound >= 0 && nums[left_bound] == target)
        {
            left_bound--;
        }
        while (right_bound < nums.size() && nums[right_bound] == target)
        {
            right_bound++;
        }
        return {left_bound + 1, right_bound - 1};
    }
}
/*
最后返回left_bound+1和right_bound-1是因为left_bound和right_bound分别是target的左边界和右边界的下一个位置。left_bound的右边一个值才是target的开始，right_bound的左边一个值才是target的结束。
*/

class Solution
{
    // lower_bound 返回最小的满足 nums[i] >= target 的下标 i
    // 如果数组为空，或者所有数都 < target，则返回 nums.size()
    // 要求 nums 是非递减的，即 nums[i] <= nums[i + 1]
    int lower_bound(vector<int> &nums, int target)
    {
        int left = 0, right = (int)nums.size() - 1; // 闭区间 [left, right]
        while (left <= right)
        { // 区间不为空
            // 循环不变量：
            // nums[left-1] < target
            // nums[right+1] >= target
            // 这种写法避免溢出。
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target)
            {
                right = mid - 1; // 范围缩小到 [left, mid-1]
            }
            else
            {
                left = mid + 1; // 范围缩小到 [mid+1, right]
            }
        }
        // 循环结束后 left = right+1
        // 此时 nums[left-1] < target 而 nums[left] = nums[right+1] >= target
        // 所以 left 就是第一个 >= target 的元素下标
        return left;
    }

    // 没有人能确保循环结束后返回的数是有效的，只能说明返回的数是第一个大于等于target的index。首先如果数=nums.size()，说明整个数组都没有大于等于target的数。其次大于等于target并不意味着target存在。如果target不存在则nums[start] != target。这种情况也要排除。
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int start = lower_bound(nums, target);
        if (start == nums.size() || nums[start] != target)
        {
            return {-1, -1}; // nums 中没有 target
        }
        // 如果 start 存在，那么 end 必定存在
        int end = lower_bound(nums, target + 1) - 1;
        return {start, end};
    }
};
