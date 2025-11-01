#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
public:
    vector<int> getAverages(vector<int> &nums, int k)
    {
        if (k == 0)
        {
            return nums;
        }
        int len = nums.size();
        long sum = 0;
        vector<int> res(len, -1);
        for (int i = 0; i < len; ++i)
        {
            if (i < k || i + k >= len)
            {
                sum += nums[i];
                continue;
            }
            if (i == k)
            {
                for (int j = 0; j <= k; ++j)
                {
                    sum += nums[i + j];
                }
                res[i] = sum / (2 * k + 1);
            }
            else
            {
                sum = sum - nums[i - k - 1] + nums[i + k];
                res[i] = sum / (2 * k + 1);
            }
        }
        return res;
    }
};