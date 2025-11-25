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
    vector<int> smallestRange(vector<vector<int>> &nums)
    {
        int k = nums.size();
        vector<pair<int, int>> merged;

        // 1. Flatten the 2D vector into pairs {value, group_index}
        for (int i = 0; i < k; ++i)
        {
            for (int num : nums[i])
            {
                merged.push_back({num, i});
            }
        }

        // 2. Sort based on value (first element of pair)
        sort(merged.begin(), merged.end());

        // 3. Separate into numbers and indexes vectors
        vector<int> numbers;
        vector<int> indexes;
        for (const auto &p : merged)
        {
            numbers.push_back(p.first);
            indexes.push_back(p.second);
        }
        int left = 0, right = 0;
        int len = merged.size();
        vector<int> foundK(k, 0);
        int notFoundCount = k;
        int minLength = INT32_MAX;
        int minLengthStart = -1;
        for (; right < len; ++right)
        {
            ++foundK[indexes[right]];
            if (foundK[indexes[right]] == 1)
            {
                --notFoundCount;
            }
            while (notFoundCount == 0)
            {
                if (minLength > numbers[right] - numbers[left])
                {
                    minLength = numbers[right] - numbers[left];
                    minLengthStart = left;
                }
                --foundK[indexes[left]];
                if (foundK[indexes[left]] == 0)
                {
                    ++notFoundCount;
                }
                ++left;
            }
        }
        return {numbers[minLengthStart], numbers[minLengthStart] + minLength};
    }
};