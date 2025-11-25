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
    long long maximumCoinsSingle(vector<vector<int>> &coins, int k)
    {
        // int len = coins.size();
        long long res = 0;
        int left = 0;
        long long covered = 0;
        for (auto &c : coins)
        {
            int carpetLeft = c[1] - k + 1;
            while (carpetLeft > coins[left][1])
            {
                covered -= (long long)(coins[left][1] - coins[left][0] + 1) * coins[left][2];
                ++left;
            }
            covered += (long long)(c[1] - c[0] + 1) * c[2];
            long long uncovered = max(0LL, (long long)(carpetLeft - coins[left][0]) * coins[left][2]);
            res = max(res, covered - uncovered);
        }
        return res;
    }
    long long maximumCoins(vector<vector<int>> &coins, int k)
    {
        ranges::sort(coins, {}, [](auto &c)
                     { return c[0]; });
        long long ans = maximumCoinsSingle(coins, k);

        ranges::reverse(coins);
        for (auto &t : coins)
        {
            int tmp = t[0];
            t[0] = -t[1];
            t[1] = -tmp;
        }
        return max(ans, maximumCoinsSingle(coins, k));
    }
};

class Solution
{
    // 2271. 毯子覆盖的最多白色砖块数（已排序）
    long long maximumWhiteTiles(vector<vector<int>> &tiles, int carpetLen)
    {
        long long ans = 0, cover = 0;
        int left = 0;
        for (auto &tile : tiles)
        {
            int tl = tile[0], tr = tile[1], c = tile[2];
            cover += (long long)(tr - tl + 1) * c;
            int carpet_left = tr - carpetLen + 1;
            while (tiles[left][1] < carpet_left)
            {
                cover -= (long long)(tiles[left][1] - tiles[left][0] + 1) * tiles[left][2];
                left++;
            }
            long long uncover = max((long long)(carpet_left - tiles[left][0]) * tiles[left][2], 0LL);
            ans = max(ans, cover - uncover);
        }
        return ans;
    }

public:
    long long maximumCoins(vector<vector<int>> &coins, int k)
    {
        ranges::sort(coins, {}, [](auto &c)
                     { return c[0]; });
        long long ans = maximumWhiteTiles(coins, k);

        ranges::reverse(coins);
        for (auto &t : coins)
        {
            int tmp = t[0];
            t[0] = -t[1];
            t[1] = -tmp;
        }
        return max(ans, maximumWhiteTiles(coins, k));
    }
};