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
    int totalFruit(vector<int> &fruits)
    {
        unordered_map<int, int> countMap;
        int left = 0, right = 0;
        int maxLen = 0;
        int len = fruits.size();
        for (; right < len; ++right)
        {
            countMap[fruits[right]]++;
            while (countMap.size() > 2)
            {
                if (--countMap[fruits[left]] == 0)
                {
                    countMap.erase(fruits[left]);
                }
                ++left;
            }
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};