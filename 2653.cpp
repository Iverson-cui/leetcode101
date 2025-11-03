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
    int getBeautyNumber(vector<int> &currArray, int x, int k)
    {
        auto it = lower_bound(currArray.begin(), currArray.end(), x);
        currArray.insert(it, x);
        return currArray[k - 1] < 0 ? currArray[k - 1] : 0;
    }
    vector<int> getSubarrayBeauty(vector<int> &nums, int k, int x)
    {
        int len = nums.size();
        vector<int> res;
        vector<int> currArray;
        for (int i = 0; i <= len - k; ++i)
        {
            if (i == 0)
            {
                currArray = vector<int>(nums.begin(), nums.begin() + k);
                sort(currArray.begin(), currArray.end());
                int temp = currArray[x - 1] < 0 ? currArray[x - 1] : 0;
                res.push_back(temp);
            }
            else
            {
                auto removeIt = find(currArray.begin(), currArray.end(), nums[i - 1]);
                currArray.erase(removeIt);
                res.push_back(getBeautyNumber(currArray, nums[i + k - 1], x));
            }
        }
        return res;
    }
};

/**
 * 上面的解法固然可以，但是每次都要进行binary search，非常费时间。可以利用题干的条件，即nums[i]在-50到50之间。
 */

class Solution
{
public:
    vector<int> getSubarrayBeauty(vector<int> &nums, int k, int x)
    {
        int len = nums.size();
        vector<int> res;
        vector<int> freq(101, 0); // Range: -50 to 50, shifted by +50

        // Initialize first window
        for (int i = 0; i < k; ++i)
        {
            freq[nums[i] + 50]++;
        }

        // Helper lambda to find x-th smallest negative number
        auto getXthSmallest = [&]() -> int
        {
            int count = 0;
            for (int i = 0; i < 50; ++i) // Only check negative numbers (0-49 in shifted range)
            {
                count += freq[i];
                if (count >= x)
                {
                    return i - 50; // Convert back to original value
                }
            }
            return 0; // No x-th smallest negative number
        };

        res.push_back(getXthSmallest());

        // Slide the window
        for (int i = k; i < len; ++i)
        {
            freq[nums[i - k] + 50]--; // Remove left element
            freq[nums[i] + 50]++;     // Add right element
            res.push_back(getXthSmallest());
        }

        return res;
    }
};