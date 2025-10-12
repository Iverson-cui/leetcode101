#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int n1 = nums1.size(), n2 = nums2.size();

        // Ensure nums1 is the smaller array for simplicity
        if (n1 > n2)
            return findMedianSortedArrays(nums2, nums1);

        int n = n1 + n2;
        int left = (n1 + n2 + 1) / 2; // Calculate the left partition size
        int low = 0, high = n1;

        while (low <= high)
        {
            // >> 1 is equivalent to / 2 but faster
            int mid1 = (low + high) >> 1; // Calculate mid index for nums1
            int mid2 = left - mid1;       // Calculate mid index for nums2

            int l1 = INT_MIN, l2 = INT_MIN, r1 = INT_MAX, r2 = INT_MAX;

            // Determine values of l1, l2, r1, and r2
            if (mid1 < n1)
                r1 = nums1[mid1];
            if (mid2 < n2)
                r2 = nums2[mid2];
            if (mid1 - 1 >= 0)
                l1 = nums1[mid1 - 1];
            if (mid2 - 1 >= 0)
                l2 = nums2[mid2 - 1];

            if (l1 <= r2 && l2 <= r1)
            {
                // The partition is correct, we found the median
                if (n % 2 == 1)
                    return max(l1, l2);
                else
                    return ((double)(max(l1, l2) + min(r1, r2))) / 2.0;
            }
            else if (l1 > r2)
            {
                // Move towards the left side of nums1
                high = mid1 - 1;
            }
            else
            {
                // Move towards the right side of nums1
                low = mid1 + 1;
            }
        }

        return 0; // If the code reaches here, the input arrays were not sorted.
    }
};

/**
 * 两个sorted array已经给定，一旦一个array的切割点给定，另一个array的切割点也随之固定。切割点的确认要满足2个条件：左右数量相同；左边的所有元素小于右边的所有元素。前者在遍历的时候保证，后者借助sorted的特点，只需要比较左边的最大值和右边的最小值即可。如果假如nums1的左边最大值大于nums2的右边最小值，说明nums1的切割点太靠右了，应该往左移，所以切割点就不可能出现在右边，这就有了二分的思想；反之亦然。最后根据总长度的奇偶性计算返回中位数。
 */