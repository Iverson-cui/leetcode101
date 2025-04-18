#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int findPeakElement(vector<int> &nums)
{
    if (nums.size() == 1)
    {
        return 0;
    }
    // first check the left and right boundary of nums
    if (nums[0] > nums[1])
    {
        return 0;
    }
    if (nums[nums.size() - 1] > nums[nums.size() - 2])
    {
        return nums.size() - 1;
    }
    int left = 1;
    int right = nums.size() - 2;
    int mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1])
        {
            return mid;
        }
        else if (nums[mid] > nums[mid - 1] && nums[mid] <= nums[mid + 1])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

/*
二分法不仅可以对有序数组进行排列，在这里寻找一个元素也可以。题目只要求找到一个符合要求的peak就可以。在使用二分法的过程中，对于mid来说，如果mid值大于边界，则这一侧可能有可能没有。但是如果mid值小于边界，这一侧一定有（可以证明）。所以直接选择mid值小于边界的那一侧。
*/