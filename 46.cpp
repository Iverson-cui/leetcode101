#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    void backtrack(vector<int> &nums, int level, vector<vector<int>> &res)
    {
        if (level == nums.size())
        {
            res.push_back(nums);
            return;
        }
        for (int i = level; i < nums.size(); ++i)
        {
            swap(nums[level], nums[i]);
            backtrack(nums, level + 1, res);
            swap(nums[level], nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res;
        backtrack(nums, 0, res);
        return res;
    }
};

/**
 * 回溯法。本题仍然是DFS的思路，遍历所有可能的组合，先确定一个，再交换剩下的。把这一个确定时的所有情况都遍历完了，再换一个确定。
 * 回溯指的是当换一个的时候，先换，递归，再换回来。保证原数据结构不变，每次都暂时换一下。
 * 回溯法常用在一个位置可以放许多个元素，每个元素又对应许多个情况的题目中。比如这里，第一个位置是1给定，第二个位置可以是2，3。所以先假设给2，在前两个位置给定的情况下探索剩余情况；然后再假设给3，接着探索剩余情况。
 */