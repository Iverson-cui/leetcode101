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
    void deltaBenefit(vector<int> &prices, vector<int> &strategy, int start, int k, long long &delta)
    {
        // long long delta = 0;
        if (start == 0)
        {
            for (int i = start; i < start + k / 2; ++i)
            {
                if (strategy[i] == -1)
                {
                    delta += prices[i];
                }
                else if (strategy[i] == 1)
                {
                    delta -= prices[i];
                }
            }
            for (int i = start + k / 2; i < start + k; ++i)
            {
                if (strategy[i] == -1)
                {
                    delta += 2 * prices[i];
                }
                else if (strategy[i] == 0)
                {
                    delta += prices[i];
                }
            }
        }
        else
        {
            if (strategy[start - 1] == -1)
            {
                delta -= prices[start - 1];
            }
            else if (strategy[start - 1] == 1)
            {
                delta += prices[start - 1];
            }
            delta -= prices[start + k / 2 - 1];
            if (strategy[start + k - 1] == -1)
            {
                delta += 2 * prices[start + k - 1];
            }
            else if (strategy[start + k - 1] == 0)
            {
                delta += prices[start + k - 1];
            }
        }
    }
    long long maxProfit(vector<int> &prices, vector<int> &strategy, int k)
    {
        long long prevBenefit = 0;
        int n = prices.size();
        for (int i = 0; i < n; ++i)
        {
            prevBenefit += (long long)prices[i] * strategy[i];
        }
        long long delta = 0;
        long long maxDelta = 0;
        for (int i = 0; i <= n - k; ++i)
        {
            deltaBenefit(prices, strategy, i, k, delta);
            maxDelta = max(maxDelta, delta);
        }
        return prevBenefit + maxDelta;
    }
};