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
    bool checkInclusion(string s1, string s2)
    {
        int len1 = s1.size();
        int len2 = s2.size();
        if (len1 > len2)
        {
            return false;
        }
        unordered_map<char, int> freq1;
        for (char c : s1)
        {
            freq1[c]++;
        }
        bool ans = false;
        unordered_map<char, int> freq2;
        for (int i = 0; i < len2; ++i)
        {
            bool temp = true;
            freq2[s2[i]]++;
            if (i < len1 - 1)
            {
                continue;
            }
            for (auto &p : freq1)
            {
                if (freq2[p.first] != p.second)
                {
                    temp = false;
                    break;
                }
            }
            if (temp)
            {
                return true;
            }
            freq2[s2[i - len1 + 1]]--;
        }
        return false;
    }
};