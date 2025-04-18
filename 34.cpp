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