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
    int longestSubarray(vector<int> &nums)
    {
        int len = nums.size();
        int left = 0, right = 0;
        int maxLen = 0;
        bool hasZero = 0;
        for (; right < len; ++right)
        {
            // cout << "Current window [" << left << ", " << right << "]: ";
            // for (int i = left; i <= right; ++i)
            // {
            //     cout << nums[i] << (i == right ? '\n' : ' ');
            // }
            if ((nums[right] == 0) && (hasZero == 1))
            {
                maxLen = max(maxLen, right - left - 1);
                while ((left < right) && (hasZero == 1))
                {

                    left++;
                    // cout << "Current window [" << left << ", " << right << "]: ";
                    // for (int i = left; i <= right; ++i)
                    // {
                    //     cout << nums[i] << (i == right ? '\n' : ' ');
                    // }
                    if (nums[left - 1] == 0)
                    {
                        break;
                    }
                }
            }
            else if (nums[right] == 0)
            {
                hasZero = 1;
            }
        }
        maxLen = max(maxLen, right - left - 1);
        return maxLen;
    }
};