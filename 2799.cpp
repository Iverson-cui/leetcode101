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
    int countCompleteSubarrays(vector<int> &nums)
    {
        unordered_set<int> uniq(nums.begin(), nums.end());
        int totalUnique = uniq.size();
        unordered_map<int, int> windowMap;
        int len = nums.size();
        int left = 0, right = 0;
        int result = 0;
        for (; right < len; ++right)
        {
            windowMap[nums[right]]++;
            while (windowMap.size() == totalUnique)
            {
                result += len - right;
                windowMap[nums[left]]--;
                if (windowMap[nums[left]] == 0)
                {
                    windowMap.erase(nums[left]);
                }
                ++left;
            }
        }
        return result;
    }
};