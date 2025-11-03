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
    int numsVal(vector<int> &nums, int len, int index)
    {
        if (index < 0)
        {
            return 0;
        }
        else if (index < nums.size())
        {
            return nums[index];
        }
        else
        {
            return nums[index - len];
        }
    }
    int minSwaps(vector<int> &nums)
    {
        int len = nums.size();
        int ones = count(nums.begin(), nums.end(), 1);
        int minSwaps = 0;
        int curSwaps = 0;
        for (int i = 0; i < len; i++)
        {
            if (i == 0)
            {
                curSwaps = count(nums.begin(), nums.begin() + ones, 0);
                minSwaps = curSwaps;
            }
            else
            {
                if (nums[i - 1] == 0)
                {
                    curSwaps -= 1;
                }
                if (numsVal(nums, len, i + ones - 1) == 0)
                {
                    curSwaps += 1;
                }
                minSwaps = min(minSwaps, curSwaps);
            }
        }
        return minSwaps;
    }
};