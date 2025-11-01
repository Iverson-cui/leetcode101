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
    long long currSum(vector<int> &nums, int &k, int &start, unordered_map<int, int> &num_set, long long &sum, unordered_set<int> &num_redundant)
    {
        if (k == 0)
        {
            return 0;
        }

        if (start == 0)
        {
            // int redundant = 0;
            for (int i = start; i < start + k; ++i)
            {
                sum += nums[i];
                if ((num_set[nums[i]]++ > 0) && (num_redundant.count(nums[i]) == 0))
                {
                    num_redundant.insert(nums[i]);
                }
            }
            if (!num_redundant.empty())
            {
                return (long long)0;
            }
            return sum;
        }
        else
        {
            sum = sum + nums[start + k - 1] - nums[start - 1];
            // has this number more than 2 times
            if (num_set[nums[start - 1]] > 2)
            {
                --num_set[nums[start - 1]];
            }
            // has this number 2 times
            else if (num_set[nums[start - 1]] == 2)
            {
                --num_set[nums[start - 1]];
                num_redundant.erase(nums[start - 1]);
            }
            // has this number 1 time
            else
            {
                num_set.erase(nums[start - 1]);
            }
            if (num_set[nums[start + k - 1]] == 0)
            {
                num_set[nums[start + k - 1]] = 1;
            }
            else if (num_set[nums[start + k - 1]] == 1)
            {
                num_set[nums[start + k - 1]] = 2;
                num_redundant.insert(nums[start + k - 1]);
            }
            // 2 times or more
            else
            {
                num_set[nums[start + k - 1]] += 1;
            }
            if (!num_redundant.empty())
            {
                return (long long)0;
            }
            else
            {
                return sum;
            }
        }
    }
    long long maximumSubarraySum(vector<int> &nums, int k)
    {
        long long sum = 0;
        int start = 0;
        int len = nums.size();
        unordered_map<int, int> num_set;
        unordered_set<int> num_redundant;
        long long max_sum = 0;
        for (start = 0; start <= len - k; ++start)
        {
            max_sum = max(max_sum, currSum(nums, k, start, num_set, sum, num_redundant));
        }
        return max_sum;
    }
};