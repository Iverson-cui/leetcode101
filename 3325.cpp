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
    int numberOfSubstrings(string s, int k)
    {
        int len = s.size();
        int left = 0, right = 0;
        int res = 0;
        int charFreq[26] = {0};
        for (; right < len; ++right)
        {
            charFreq[s[right] - 'a']++;
            char currChar = s[right];
            while (charFreq[currChar - 'a'] >= k)
            {
                res += len - right;
                charFreq[s[left] - 'a']--;
                ++left;
            }
        }
        return res;
    }
};