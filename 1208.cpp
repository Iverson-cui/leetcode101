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
    int equalSubstring(string s, string t, int maxCost)
    {
        vector<int> costs;
        for (int i = 0; i < s.length(); i++)
        {
            costs.push_back(abs(s[i] - t[i]));
        }
        sort(costs.begin(), costs.end());
        int len = costs.size();
        int right = 0;
        int totalCost = 0;
        for (; right < len; ++right)
        {
            if (totalCost + costs[right] > maxCost)
            {
                break;
            }
            totalCost += costs[right];
        }
        return right;
    }
};

/**
 * 以上的解法是最大能转化的char的数量，但是题目要求子字符串，即转化过的字符串应该是连续的。
 */

class Solution
{
public:
    int equalSubstring(string s, string t, int maxCost)
    {
        vector<int> costs;
        for (int i = 0; i < s.length(); i++)
        {
            costs.push_back(abs(s[i] - t[i]));
        }
        int len = costs.size();
        int left = 0, right = 0;
        int totalCost = 0;
        int maxLen = 0;
        for (; right < len; ++right)
        {
            while (totalCost + costs[right] > maxCost)
            {
                maxLen = max(maxLen, right - left);
                totalCost -= costs[left];
                ++left;
            }
            totalCost += costs[right];
            // maxLen = max(maxLen, right - left + 1);
        }
        return max(maxLen, right - left);
        ;
    }
};