#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
public:
    int isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
    int maxVowels(string s, int k)
    {
        int currCount = 0;
        int maxCount = 0;
        int len = s.size();
        // left and right pointers
        int end = k - 2;
        int begin = 0;
        for (int i = 0; i < k - 1; ++i)
        {
            if (isVowel(s[i]))
            {
                ++maxCount;
            }
        }
        currCount = maxCount;
        while (end < len - 1)
        {
            ++end;
            if (isVowel(s[end]))
            {
                ++currCount;
            }
            maxCount = max(maxCount, currCount);
            if (isVowel(s[begin]))
            {
                --currCount;
            }
            ++begin;
        }
        return maxCount;
    }
};