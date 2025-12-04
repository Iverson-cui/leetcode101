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
    long long minNumberOfSeconds(int mountainHeight, vector<int> &workerTimes)
    {
        auto check = [&](long long m)
        {
            int left_h = mountainHeight;
            for (int t : workerTimes)
            {
                left_h -= ((int)sqrt(m / t * 8 + 1) - 1) / 2;
                if (left_h <= 0)
                {
                    return true;
                }
            }
            return false;
        };

        int max_t = ranges::max(workerTimes);
        int h = (mountainHeight - 1) / workerTimes.size() + 1;
        long long left = 0, right = (long long)max_t * h * (h + 1) / 2;
        while (left + 1 < right)
        {
            long long mid = (left + right) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right;
    }
};

/**
 * 第一遍做没做出来。二分很好想，重点是判断某个给出的数可不可行的helper function比较难写，需要解一个二元一次方程同时还有多个上下取整防缩操作。
 */