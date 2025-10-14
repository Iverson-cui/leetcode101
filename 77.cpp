#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    void backtrack(vector<int> &comb, vector<vector<int>> &res, int level, int n, int k)
    {
        if (comb.size() == k)
        {
            res.push_back(comb);
            return;
        }
        // 当前的comb有多少元素无关紧要，需要记录的是当前push的是哪个元素，以后再push只能比这个元素大。
        for (int i = level; i < n; i++)
        {
            comb.push_back(i);
            backtrack(comb, res, i + 1, n, k);
            comb.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k)
    {
        // all possible combinations
        vector<vector<int>> res;
        // current combination
        vector<int> comb;
        backtrack(comb, res, 1, n + 1, k);
        return res;
    }
};

/**
 * 也是回溯法，先将当前的数字push进我们维护的comb，递归，接着在pop出来，下一个循环push进更新的
 */