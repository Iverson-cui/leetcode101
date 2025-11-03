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
    int replaceNum(vector<int> &code, int index, int k, int len)
    {
        int sum = 0;
        if (k > 0)
        {
            for (int i = 1; i <= k; ++i)
            {
                sum += code[(index + i) % len];
            }
        }
        else if (k < 0)
        {
            for (int i = 1; i <= -k; ++i)
            {
                sum += code[(index - i + len) % len];
            }
        }
        else
        {
            return 0;
        }
        return sum;
    }
    vector<int> decrypt(vector<int> &code, int k)
    {
        int len = code.size();
        vector<int> res(len, 0);
        for (int i = 0; i < len; ++i)
        {
            res[i] = replaceNum(code, i, k, len);
        }
        return res;
    }
};