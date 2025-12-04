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
    vector<int> getSetBitIndices(int n)
    {
        vector<int> indices;
        for (int i = 0; i < 32; ++i)
        {
            // Check if the i-th bit is set
            if ((n >> i) & 1)
            {
                indices.push_back(i);
            }
        }
        return indices;
    }
    int longestNiceSubarray(vector<int> &nums)
    {
        int len = nums.size();
        int left = 0, right = 0;
        int result = 1;
        int bit1Pos[32] = {0};
        int bit1Count = 0;
        for (; right < len; ++right)
        {
            vector<int> temp = getSetBitIndices(nums[right]);
            for (int pos : temp)
            {
                bit1Pos[pos]++;
                if (bit1Pos[pos] == 2)
                {
                    bit1Count++;
                }
            }
            while (bit1Count > 0)
            {
                temp = getSetBitIndices(nums[left]);
                for (int pos : temp)
                {
                    bit1Pos[pos]--;
                    if (bit1Pos[pos] == 1)
                    {
                        bit1Count--;
                    }
                }
                left++;
            }
            result = max(result, right - left + 1);
        }
        return result;
    }
};

/**
 * 这种方法固然可以，但是复杂度较高。
 * 下面的做法用集合和位运算来做，效率更高。这个题本质上其实是脑筋急转弯问题。
 */

class Solution
{
public:
    int longestNiceSubarray(vector<int> &nums)
    {
        int ans = 0, left = 0, or_ = 0;
        for (int right = 0; right < nums.size(); right++)
        {
            while (or_ & nums[right])
            {                        // 有交集
                or_ ^= nums[left++]; // 从 or 中去掉集合 nums[left]
            }
            or_ |= nums[right]; // 把集合 nums[right] 并入 or 中
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};