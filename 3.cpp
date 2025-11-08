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
    int lengthOfLongestSubstring(string s)
    {
        int len = s.length();
        int left = 0, right = 0;
        int maxLen = 0;
        // int currLen = 0;
        unordered_set<char> appearedChars;
        while ((right < len) && (left <= right))
        {
            if (appearedChars.count(s[right]) == 0)
            {
                ++right;
                // ++currLen;
                printf("left: %d, right: %d\n", left, right);
                appearedChars.insert(s[right - 1]);
            }
            else
            {
                maxLen = max(maxLen, right - left);
                while (s[left] != s[right])
                {
                    ++left;
                    // --currLen;
                    printf("left: %d, right: %d\n", left, right);
                    appearedChars.erase(s[left - 1]);
                }
                ++left;
                // --currLen;
                appearedChars.erase(s[left - 1]);
                printf("left: %d, right: %d\n", left, right);
            }
        }
        maxLen = max(maxLen, right - left);
        return maxLen;
    }
};

/**
 * 以下附上标准的滑动窗口解法作为参考：主体是一个for循环，判断条件是右边界和字符串长度的比较。
 */

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int n = s.length(), ans = 0, left = 0;
        unordered_set<char> window; // 维护从下标 left 到下标 right 的字符
        for (int right = 0; right < n; right++)
        {
            char c = s[right];
            // 如果窗口内已经包含 c，那么再加入一个 c 会导致窗口内有重复元素
            // 所以要在加入 c 之前，先移出窗口内的 c
            while (window.count(c))
            { // 窗口内有 c
                window.erase(s[left]);
                left++; // 缩小窗口
            }
            window.insert(c);                 // 加入 c
            ans = max(ans, right - left + 1); // 更新窗口长度最大值
        }
        return ans;
    }
};