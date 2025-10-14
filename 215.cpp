#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    int findKthLargest(vector<int> nums, int k)
    {
        int pivot = rand() % nums.size();
        int pivot_val = nums[pivot];
        vector<int> larger, equal, smaller;
        for (int num : nums)
        {
            if (num > pivot_val)
            {
                larger.push_back(num);
            }
            else if (num < pivot_val)
            {
                smaller.push_back(num);
            }
            else
            {
                equal.push_back(num);
            }
        }
        // k-th element in larger array
        if (k <= larger.size())
        {
            return findKthLargest(larger, k);
        }
        // k-th element in smaller array
        if (k > larger.size() + equal.size())
        {
            return findKthLargest(smaller, k - larger.size() - equal.size());
        }
        return pivot_val;
    }
};

/**
 * 快速选择和快速排序类似。快速排序是选择一个pivot，对前后进行排序，递归call，传入前面和后面。而快速选择只需要将大的，相等的，小的分开，看数量就可以。如果larger size大于k，则要找的元素在larger里；如果larger+equal的size小于k，则要找的元素在smaller里；最后的情况是k在equal里，这个时候直接返回当前的pivot即可。
 */