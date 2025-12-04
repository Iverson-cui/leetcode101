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
    long long countSubarrays(vector<int> &nums, long long k)
    {
        int len = nums.size();
        int left = 0, right = 0;
        long long total = 0;
        long long result = 0;
        for (; right < len; ++right)
        {
            total += nums[right];
            // int score = total * (right - left + 1);
            while (total * (right - left + 1) >= k)
            {
                total -= nums[left];
                ++left;
            }
            result += right - left + 1;
        }
        return result;
    }
};