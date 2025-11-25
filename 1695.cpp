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
    int maximumUniqueSubarray(vector<int> &nums)
    {
        int len = nums.size();
        int left = 0, right = 0;
        unordered_set<int> window;
        int maxSum = 0, currentSum = 0;
        for (; right < len; ++right)
        {
            if (window.count(nums[right]) == 0)
            {
                currentSum += nums[right];
                window.insert(nums[right]);
                maxSum = max(maxSum, currentSum);
            }
            else
            {
                while (window.count(nums[right]) > 0)
                {
                    window.erase(nums[left]);
                    currentSum -= nums[left];
                    ++left;
                }
                --right; // stay at the same right to reprocess
            }
            maxSum = max(maxSum, currentSum);
        }
        return maxSum;
    }
};

/**
 * 最通用的想法就是unordered_set和unordered_map，但是有的时候费时费空间。
 * 下面的实现先找出了nums里的最大值，以这个值的大小来创建一个bool数组。数组的元素是int8，这是值得注意的一点，因为数组本身的目的是bool，但是创建为int8会使得数组的访问和修改更快。bool本身只占一位，如果访问特定的一个bit，需要先定位到对应的byte，然后进行位操作来读写这个bit，这样就多了几步操作。而int8直接对应一个byte，访问和修改都只需要一步内存读写操作，所以速度更快。当然带来的缺陷是8倍的内存消耗。
 * 需要注意的是，之前刷题的时候接触到的unordered_set和unordered_map虽然在查找问题上是O(1)的，但是实际上还是不如vector快。相比于二分查找等等方法确实是unordered_Set更快，但是对于直接更改某个memory的内存，显然array又快又省空间。
 */

class Solution
{
public:
    int maximumUniqueSubarray(vector<int> &nums)
    {
        int mx = ranges::max(nums);
        vector<int8_t> has(mx + 1);
        int ans = 0, s = 0, left = 0;
        for (int x : nums)
        {
            while (has[x])
            {
                has[nums[left]] = false;
                s -= nums[left];
                left++;
            }
            has[x] = true;
            s += x;
            ans = max(ans, s);
        }
        return ans;
    }
};
