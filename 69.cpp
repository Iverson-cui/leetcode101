#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int mySqrt(int x)
{
    int left = 0;
    int right = x;
    int mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (mid == 0)
        {
            if (x == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        if (mid == x / mid)
        {
            return mid;
        }
        else if (mid < x / mid)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return right;
}

int main(void)
{
    int test = 8;
    mySqrt(test);
    return 0;
}

/*
注意，求mid的时候可以用（left+right）/2，但是有可能会出现溢出的情况。
left=mid+1 right=mid-1 是因为当更新mid的时候已经判断完mid不符合情况了，所以下一个回合把mid排除掉，从mid的旁边的值开始。
最后不符合情况下返回的是right。
二分法最棘手的情况就是左右区间开闭的问题，mid更新取值问题和最终return问题。
*/