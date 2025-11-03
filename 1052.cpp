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
    int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int minutes)
    {
        int len = customers.size();
        int max_extra = 0;
        int current_extra = 0;
        int base_satisfied = 0;
        for (int i = 0; i < len; ++i)
        {
            base_satisfied += customers[i] * (1 - grumpy[i]);
        }
        if (len == 1)
        {
            return base_satisfied + customers[0] * grumpy[0];
        }
        for (int i = 0; i < len; ++i)
        {
            if (i < minutes)
            {
                current_extra += customers[i] * grumpy[i];
                max_extra = current_extra;
            }
            // else if (i == minutes)
            // {
            //     max_extra = current_extra;
            //     current_extra = current_extra - customers[i - minutes] * grumpy[i - minutes] + customers[i] * grumpy[i];
            //     max_extra = max(max_extra, current_extra);
            // }
            else
            {
                current_extra += customers[i] * grumpy[i];
                current_extra -= customers[i - minutes] * grumpy[i - minutes];
                max_extra = max(max_extra, current_extra);
            }
        }
        return max_extra + base_satisfied;
    }
};