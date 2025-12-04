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
    bool canEatAll(vector<int> &piles, int h, int speed)
    {
        long long hoursSpent = 0;
        for (auto pile : piles)
        {
            hoursSpent += (pile + speed - 1) / speed;
        }
        return hoursSpent <= h;
    }
    int minEatingSpeed(vector<int> &piles, int h)
    {
        int left = 1, right = *ranges::max_element(piles);
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (canEatAll(piles, h, mid))
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