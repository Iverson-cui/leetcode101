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
    long long nearly_unique(vector<int> &nums, unordered_map<int, int> &num_appearance, int m, int k, int start, long long &cur_sum, int &cur_num_unique)
    {
        // first time call, update cur_num_unique, cur_sum and num_appearance
        if (start == 0)
        {
            for (int i = start; i < start + k; ++i)
            {
                if (num_appearance.count(nums[i]) == 0)
                {
                    cur_num_unique++;
                }
                num_appearance[nums[i]]++;
                cur_sum += nums[i];
            }
            // return cur_sum;
        }
        else
        {
            // update cur_sum
            cur_sum = cur_sum + nums[start + k - 1] - nums[start - 1];
            // update num_appearance and cur_num_unique
            if (--num_appearance[nums[start - 1]] == 0)
            {
                num_appearance.erase(nums[start - 1]);
                cur_num_unique--;
            }
            if (num_appearance.count(nums[start + k - 1]) == 0)
            {
                cur_num_unique++;
            }
            ++num_appearance[nums[start + k - 1]];
        }
        if (cur_num_unique >= m)
        {
            return cur_sum;
        }
        else
        {
            return -1;
        }
    }
    long long maxSum(vector<int> &nums, int m, int k)
    {
        long long cur_sum = 0;
        long long max_sum = 0;
        int cur_num_unique = 0;
        int len = nums.size();
        unordered_map<int, int> num_appearance;
        for (int i = 0; i < len - k + 1; ++i)
        {
            if (nearly_unique(nums, num_appearance, m, k, i, cur_sum, cur_num_unique) != -1)
            {
                max_sum = max(max_sum, cur_sum);
            }
        }
        return max_sum;
    }
};

/**
 * 充分利用滑动窗口中部分更新的思想，不要每次都处理窗口里的所有元素，而是着重看窗口新扩进来的和之前移出去的元素，避免超时。可以使用pass by reference的方法来保留之前的状态。
 */