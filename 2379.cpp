#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
public:
    int minimumRecolors(string blocks, int k)
    {
        int len = blocks.length();
        int min_ops = k;
        // int cur_ops = 0;
        for (int j = 0; j < k; ++j)
        {
            if (blocks[j] == 'B')
            {
                --min_ops;
            }
        }
        // min_ops = min(min_ops, cur_ops);
        int cur_ops = min_ops;
        for (int i = 1; i <= len - k; ++i)
        {
            int prev = (blocks[i - 1] == 'W') ? 1 : 0;
            int after = (blocks[i + k - 1] == 'W') ? 1 : 0;
            cur_ops += after - prev;
            min_ops = min(min_ops, cur_ops);
            if (min_ops == 0)
            {
                return 0;
            }
        }
        return min_ops;
    }
};