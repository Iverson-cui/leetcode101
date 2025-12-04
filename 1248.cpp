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
    int evenBiggerThanK(vector<int> &nums, int k)
    {
        int len = nums.size();
        int evenCount = 0;
        int left = 0, right = 0;
        int result = 0;
        for (; right < len; ++right)
        {
            if (nums[right] % 2 == 1)
            {
                evenCount++;
            }
            while (evenCount >= k)
            {
                result += (len - right);
                if (nums[left] % 2 == 1)
                {
                    evenCount--;
                }
                left++;
            }
        }
        return result;
    }
    int numberOfSubarrays(vector<int> &nums, int k)
    {
        return evenBiggerThanK(nums, k) - evenBiggerThanK(nums, k + 1);
    }
};