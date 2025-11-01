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
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;

        vector<int> comb;
        dfs(candidates, target, 0, comb, res);
        return res;
    }

    void dfs(vector<int> &candidates, int target, int start, vector<int> &comb, vector<vector<int>> &res)
    {
        if (target < 0)
        {
            return;
        }

        if (target == 0)
        {
            res.push_back(comb);
            return;
        }

        for (int i = start; i < candidates.size(); i++)
        {
            // avoid duplicate combinations
            if (i > start && candidates[i] == candidates[i - 1])
            {
                continue;
            }

            if (candidates[i] > target)
            {
                break;
            }

            comb.push_back(candidates[i]);
            dfs(candidates, target - candidates[i], i + 1, comb, res);
            comb.pop_back();
        }
    }
};

/**
 * 处理duplicate的方法是：如果当前数字和前一个数字相同，并且不是本层递归的第一个数字，就跳过它。因为既然已经处理到当前了，前面的相同数字已经被处理过了。再处理只会得到相同的结果。
 */