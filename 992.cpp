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
    int solve(vector<int> &nums, int k)
    {
        int len = nums.size();
        int left = 0, right = 0;
        int count = 0;
        unordered_map<int, int> numCount;
        int distinctCount = 0;
        long long result = 0;
        for (; right < len; ++right)
        {
            numCount[nums[right]]++;
            if (numCount[nums[right]] == 1)
            {
                distinctCount++;
            }
            while (distinctCount >= k)
            {
                result += (len - right);
                numCount[nums[left]]--;
                if (numCount[nums[left]] == 0)
                {
                    distinctCount--;
                }
                left++;
            }
        }
        return result;
    }
    int subarraysWithKDistinct(vector<int> &nums, int k)
    {
        return solve(nums, k) - solve(nums, k + 1);
    }
};