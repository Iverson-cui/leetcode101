#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    int singleNonDuplicate(vector<int> &nums)
    {
        int len = nums.size();
        // len is odd, but we need to find the len of each half
        int half_odd = ((len - 1) / 2) % 2;
        // mid is the middle point
        int mid = (len - 1) / 2;
        if (mid == 0)
        {
            return nums[0];
        }
        if (nums[mid] == nums[mid - 1])
        {
            if (half_odd == 1)
            {
                vector<int> later_half(nums.begin() + mid + 1, nums.end());
                return singleNonDuplicate(later_half);
            }
            else
            {
                vector<int> first_half(nums.begin(), nums.begin() + mid + 1);
                return singleNonDuplicate(first_half);
            }
        }
        else if (nums[mid] == nums[mid + 1])
        {
            if (half_odd == 1)
            {
                vector<int> first_half(nums.begin(), nums.begin() + mid);
                return singleNonDuplicate(first_half);
            }
            else
            {
                vector<int> later_half(nums.begin() + mid, nums.end());
                return singleNonDuplicate(later_half);
            }
        }
        else
        {
            return nums[mid];
        }
    }
};

/**
 * 以上的解法虽然时间上有优势，但是空间上没有优势，因为要复制vector再反复传入。正确的做法是找两个指针标志array的头和尾，计算mid。根据mid，头和尾的index来确定到底是前半部分还是后半部分。到最后return一下。下面是完美解法。
 */

class Solution
{
public:
    int singleNonDuplicate(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if ((mid % 2 == 0 && nums[mid] == nums[mid + 1]) || (mid % 2 == 1 && nums[mid] == nums[mid - 1]))
                left = mid + 1;
            else
                right = mid;
        }

        return nums[left];
    }
};