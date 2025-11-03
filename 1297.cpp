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
    int maxFreq(string s, int maxLetters, int minSize, int maxSize)
    {
        unordered_map<char, int> charCount;
        unordered_map<string, int> substringCount;
        int len = s.size();
        for (int i = 0; i <= len - minSize; ++i)
        {
            if (i == 0)
            {
                for (int j = 0; j < minSize; ++j)
                {
                    charCount[s[j]]++;
                }
            }
            else
            {
                if (charCount[s[i - 1]] == 1)
                {
                    charCount.erase(s[i - 1]);
                }
                else
                {
                    charCount[s[i - 1]]--;
                }
                charCount[s[i + minSize - 1]]++;
            }
            if (charCount.size() <= maxLetters)
            {
                substringCount[s.substr(i, minSize)]++;
            }
        }
        int maxFreq = 0;
        for (const auto &pair : substringCount)
        {
            maxFreq = max(maxFreq, pair.second);
        }
        return maxFreq;
    }
};

/**
 * 题目要求返回满足条件的某一个字符串出现的最大次数，重要的一步是对问题进行化简，即考虑到任何只要是长度大于minSize且满足条件的字符串的出现，必定意味着其任意子串也出现相同的次数，但是子串出现并不意味着比其长度更长的出现，所以字串的出现次数肯定是大于等于长串。题中要求返回最大的满足条件的字符串的出现次数，其实只需要考虑子串的出现次数即可。
 */