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
    long long countSubarrays(vector<int> &nums, int k)
    {
        int len = nums.size();
        int left = 0, right = 0;
        long long res = 0;
        int cnt = 0;
        int maxNum = *max_element(nums.begin(), nums.end());
        for (; right < len; ++right)
        {
            if (nums[right] == maxNum)
            {
                cnt++;
            }
            while (cnt >= k)
            {
                res += len - right;
                if (nums[left] == maxNum)
                {
                    cnt--;
                }
                ++left;
            }
        }
        return res;
    }
};