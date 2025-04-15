#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
bool isPalindrome(string s)
{
    int left = 0;
    int right = s.length() - 1;
    while (left < right)
    {
        if (s[left] != s[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

bool validPalindrome(string s)
{

    int left = 0;
    int right = s.length() - 1;
    if (s.length() < 3)
    {
        return true;
    }
    while (left < right)
    {
        if (s[left] != s[right])
        {
            return isPalindrome(s.substr(left + 1, right - left)) || isPalindrome(s.substr(left, right - left));
        }

        left++;
        right--;
    }
    return true;
}

/*
基本思路很简单，就是通过双指针前后确认是否相同，相同就移动一位。但是这里涉及到类似recursive的编程思想。如果当前不相同，去除左边或右边的字符，判断剩下的字符串是不是回文。因为只能去除一次，所以要新写一个函数，其在给定字符串不去除任何字符的情况下判断是否是回文。如果不recursive的想，就需要判断很多情况，十分琐碎难写。
*/