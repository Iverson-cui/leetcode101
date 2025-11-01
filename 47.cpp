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
    void recursion(vector<int> num, int i, int j, vector<vector<int>> &res)
    {
        if (i == j - 1)
        {
            res.push_back(num);
            return;
        }
        for (int k = i; k < j; k++)
        {
            if (i != k && num[i] == num[k])
                continue;
            swap(num[i], num[k]);
            recursion(num, i + 1, j, res);
        }
    }
    vector<vector<int>> permuteUnique(vector<int> &num)
    {
        sort(num.begin(), num.end());
        vector<vector<int>> res;
        recursion(num, 0, num.size(), res);
        return res;
    }
};

/**
 * 因为顺序是无所谓的，所以可以随意打乱顺序。排序是为了能检测duplicate。如果不排序，无法确认当前的值是否有duplicate。通过排序，直接将他和开始的值进行比较即可。
 * 因为是pass by value，所以后续的更改只在自己的local copy上生效。这是故意的，否则当swap i和j之后，再次swap i和j+1的时候，j+1的位置已经不是原来的值了。
 */