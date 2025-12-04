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
    long long validSubstringCount(string word1, string word2)
    {
        unordered_map<char, int> charIndicesMap;
        int len1 = word1.size();
        int len2 = word2.size();
        for (char c : word2)
        {
            charIndicesMap[c]++;
        }
        long long result = 0;
        int satisfyCharCount = charIndicesMap.size();
        int left = 0, right = 0;
        for (; right < len1; ++right)
        {
            --charIndicesMap[word1[right]];
            if (charIndicesMap[word1[right]] == 0)
            {
                satisfyCharCount--;
            }
            while (satisfyCharCount == 0)
            {
                result += (long long)(len1 - right);
                ++charIndicesMap[word1[left]];
                if (charIndicesMap[word1[left]] == 1)
                {
                    satisfyCharCount++;
                }
                ++left;
            }
        }
        return result;
    }
};

/**
 * 思路没错，但是能从2点优化：early termination，即如果len1<len2直接return 0；用array代替unordered_map。
 * unordered_map被用在如果index很大且不连续，index不是int等情况，这个时候用array来存储很浪费空间。
 */