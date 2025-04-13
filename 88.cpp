#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    int pos = m-- + n-- - 1;
    while (m >= 0 && n >= 0)
    {
        nums1[pos--] = nums1[m] > nums2[n] ? nums1[m--] : nums2[n--];
    }
    while (n >= 0)
    {
        nums1[pos--] = nums2[n--];
    }
}

int main(void)
{
    vector<int> nums1 = {2, 2, 3, 9, 0, 0, 0};
    vector<int> nums2 = {1, 1, 1};
    int m = 4;
    int n = 3;
    merge(nums1, m, nums2, n);
    for (int i = 0; i < nums1.size(); i++)
    {
        cout << nums1[i] << " ";
    }
    cout << endl;
    return 0;
}

/*
不要想复杂，就是很简单的2个指针分别对准2个数组的元素，还有一个指针指向要插入的位置。需要思考的是哪个数组先dry。如果是nums2就不需要额外处理，如果是nums1就需要把所有nums2剩余的元素放到nums1前面。
*/