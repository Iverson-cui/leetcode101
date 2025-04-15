#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

bool judgeSquareSum(int c)
{
    int left = 0;
    long right = sqrt(c);
    while (left <= right)
    {
        long temp = left * left + right * right;
        if (temp == c)
        {
            return true;
        }
        else if (temp < c)
        {
            left++;
        }
        else
        {
            right--;
        }
    }
    return false;
}

/*
原来将3个数全部设为int，会出现溢出。都设为long会导致内存使用过多。将小的设为int 大的设为long，会减少内存满足条件。
思路是：a和b最大也就是sqrt（），从sqrt往下寻找。注意2个指针不是同步运动的，一个会让平方和变大，一个会让平方和变小。要根据平方和和目标的大小实时评估，一次只动一个指针。
*/