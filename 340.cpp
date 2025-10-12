#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

/**
 * Given a string s and an integer k, return the length of the longest substring of s that contains at most k distinct characters.
 */

class Solution
{
public:
    int lengthOfLongestSubstringKDistinct(string s, int k)
    {
        unordered_map<char, int> cnt;
        int l = 0;
        for (char &c : s)
        {
            ++cnt[c];
            if (cnt.size() > k)
            {
                if (--cnt[s[l]] == 0)
                {
                    cnt.erase(s[l]);
                }
                ++l;
            }
        }
        return s.size() - l;
    }
};

/**
 * 其实就是双指针做滑动窗口，另外找一个数据结构来维护当前范围内的字符种类和数量，一旦不符合条件，就upd左边界，符合条件就upd右边界。
 */