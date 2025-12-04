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
    bool help(vector<int> &time, int &totalTrips, long long timeGiven)
    {
        long long trips = 0;
        for (int t : time)
        {
            trips += timeGiven / t;
        }
        return totalTrips <= trips;
    }
    long long minimumTime(vector<int> &time, int totalTrips)
    {
        int minTime = *ranges::min_element(time);
        long long left = 1, right = (long long)minTime * totalTrips - 1LL;
        while (left <= right)
        {
            long long mid = left + (right - left) / 2;
            if (help(time, totalTrips, mid))
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