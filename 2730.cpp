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
    int longestSemiRepetitiveSubstring(string s)
    {
        int len = s.size();
        int left = 0, right = 1;
        int numRepetitions = 0;
        int maxLen = 2;
        if (len < 2)
        {
            return len;
        }
        for (; right < len; ++right)
        {
            if (s[right] == s[right - 1])
            {
                ++numRepetitions;
            }
            while (numRepetitions > 1)
            {
                ++left;
                if (s[left] == s[left - 1])
                {
                    --numRepetitions;
                }
            }
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};