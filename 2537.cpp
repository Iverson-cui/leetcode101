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
    long long countGood(vector<int> &nums, int k)
    {
        int len = nums.size();
        unordered_map<int, int> windowMap;
        int left = 0, right = 0;
        long long result = 0;
        int pair = 0;
        for (; right < len; ++right)
        {
            windowMap[nums[right]]++;
            pair += windowMap[nums[right]] - 1;
            while (pair >= k)
            {
                result += len - right;
                windowMap[nums[left]]--;
                pair -= windowMap[nums[left]];
                ++left;
            }
        }
        return result;
    }
};