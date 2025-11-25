#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

class Solution
{
public:
    string shortestBeautifulSubstring(string s, int k)
    {
        if (ranges::count(s, '1') < k)
        {
            return "";
        }
        string ans = s;
        int cnt1 = 0, left = 0;
        for (int right = 0; right < s.length(); right++)
        {
            cnt1 += s[right] - '0';
            while (cnt1 > k || s[left] == '0')
            {
                cnt1 -= s[left++] - '0';
            }
            if (cnt1 == k)
            {
                string t = s.substr(left, right - left + 1);
                if (t.length() < ans.length() || t.length() == ans.length() && t < ans)
                {
                    ans = move(t);
                }
            }
        }
        return ans;
    }
};

/**
 * 题里提到的字典序dictionary order或者叫lexicographical order，是指字符串按照字母表顺序进行比较的方式。这个方法可以直接用C++的字符串比较运算符<和>来实现。
 */