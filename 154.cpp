#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int findMin(vector<int> &nums)
{
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi)
    {
        int mi = lo + (hi - lo) / 2;
        // rotate point is in the right
        if (nums[mi] > nums[hi])
        {
            lo = mi + 1;
        }
        // rotate point is in the left
        else if (nums[mi] < nums[lo])
        {
            hi = mi;
            lo++;
        }
        else
        { // nums[lo] <= nums[mi] <= nums[hi]
            hi--;
        }
    }

    return nums[lo];
}

int main()
{
    vector<int> nums = {2, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1};
    cout << findMin(nums) << endl;
    return 0;
}

/*
normally we would update left and right by left=mid+1 and right=mid-1, but here we couldn't do it for case when nums[mid]<nums[low] because we want to find the minumum number, so mid may be the one, we cannot skip it.
*/