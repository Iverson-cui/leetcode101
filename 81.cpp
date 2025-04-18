#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

bool search(vector<int> &nums, int target)
{
    int l = 0;
    int r = nums.size() - 1;

    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target)
            return true;
        // with duplicates we can have this contdition, just update left & right
        if ((nums[l] == nums[mid]) && (nums[r] == nums[mid]))
        {
            l++;
            r--;
        }
        // first half
        // first half is in order
        else if (nums[l] <= nums[mid])
        {
            // target is in first  half
            if ((nums[l] <= target) && (nums[mid] > target))
                r = mid - 1;
            else
                l = mid + 1;
        }
        // second half
        // second half is order
        // target is in second half
        else
        {
            if ((nums[mid] < target) && (nums[r] >= target))
                l = mid + 1;
            else
                r = mid - 1;
        }
    }
    return false;
}

int main(void)
{
    vector<int> test = {1, 0, 1, 1, 1};
    int target = 0;
    cout << search(test, target) << endl;
    return 0;
}
/*
如果没有重复元素，直接找mid。因为整个数组是部分有序的，所以能直接判断mid在哪边。接着判断target在哪边。
有重复元素就无法直接判断mid在哪边了。
*/