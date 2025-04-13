#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

vector<int> twoSum(vector<int> &numbers, int target)
{
    int begin = 0;
    int end = numbers.size() - 1;
    vector<int> result;
    // begin = numbers[0];
    // end = &numbers[numbers.size() - 1];
    // iterate until begin and end meet
    while (begin < end)
    {
        if (numbers[begin] + numbers[end] == target)
        {
            // if we found the target
            result.push_back(begin + 1);
            result.push_back(end + 1);
            return result;
        }
        else if (numbers[begin] + numbers[end] < target)
        {
            begin += 1;
        }
        else
        {
            end -= 1;
        }
    }
    return result;
}

/*
双指针解法。一个指针在头一个指针在尾，用来搜索。
说是双指针，不一定非得2个指针元素，对于vector来说，用[]遍历和用指针遍历是等价的。可以直接用2个int元素遍历，节省空间。双指针只是一个思想不是具体的实现方法。
*/