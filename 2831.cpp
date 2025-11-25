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
    int longestEqualSubarray(vector<int> &nums, int k)
    {
        int len = nums.size();
        vector<int> count(len + 1, 0);
        int left = 0, right = 0, ans = 0;
        int currentMaxIndex = 0;
        for (; right < len; ++right)
        {
            count[nums[right]]++;
            if (count[currentMaxIndex] < count[nums[right]])
            {
                currentMaxIndex = nums[right];
            }
            while (right - left + 1 - count[currentMaxIndex] > k)
            {
                ++left;
                count[nums[left - 1]]--;
                if (nums[left - 1] == currentMaxIndex)
                {
                    currentMaxIndex = int(max_element(count.begin(), count.end()) - count.begin());
                }
            }
            ans = max(ans, count[currentMaxIndex]);
        }
        return ans;
    }
};

/**
 * 以上的解法可以做，但是费时间，因为需要一直判断处理的元素是否是最大。像这种在随着窗口左右边界的变化，我们关心的值也在变化的情况，每次都判断很费时间，换个思路。
 */

class Solution
{
public:
    int longestEqualSubarray(vector<int> &nums, int k)
    {
        int n = nums.size();
        // maintains the index of each number in the list
        vector<vector<int>> pos_lists(n + 1);
        for (int i = 0; i < n; i++)
        {
            int x = nums[i];
            pos_lists[x].push_back(i - pos_lists[x].size());
        }

        // iterate through each number pair
        int ans = 0;
        for (auto &pos : pos_lists)
        {
            int left = 0;
            for (int right = 0; right < pos.size(); right++)
            {
                while (pos[right] - pos[left] > k)
                { // 要删除的数太多了
                    left++;
                }
                ans = max(ans, right - left + 1);
            }
        }
        return ans;
    }
};

/**
 * 按照424的滑动窗口解法，当然也可以，只不过424中元素是字符，一共最多26个，这里不一定，所以复杂度会上升。解法超出时间限制，但是本身没有错误。
 */

class Solution
{
public:
    int longestEqualSubarray(vector<int> &nums, int k)
    {
        int len = nums.size();
        vector<bool> occurs(len + 1, false);
        int maxLen = 0;
        for (auto &num : nums)
        {
            occurs[num] = true;
        }
        for (int i = 0; i <= len; ++i)
        {
            int count = 0;
            if (occurs[i] == 0)
            {
                continue;
            }
            int left = 0, right = 0;
            for (; right < len; ++right)
            {
                if (nums[right] != i)
                {
                    count++;
                }
                while (count > k)
                {
                    if (nums[left] != i)
                    {
                        count--;
                    }
                    left++;
                }
                maxLen = max(maxLen, right - left + 1 - count);
            }
        }
        return maxLen;
    }
};
