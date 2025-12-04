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
    bool canShip(vector<int> &weights, int days, int capacity)
    {
        int currentLoad = 0;
        int requiredDays = 1;
        for (auto weight : weights)
        {
            if (currentLoad + weight > capacity)
            {
                ++requiredDays;
                currentLoad = weight;
            }
            else
            {
                currentLoad += weight;
            }
        }
        return requiredDays <= days;
    }
    int shipWithinDays(vector<int> &weights, int days)
    {
        int left = *ranges::max_element(weights);
        int right = accumulate(weights.begin(), weights.end(), 0) - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (canShip(weights, days, mid))
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left;
    }
};