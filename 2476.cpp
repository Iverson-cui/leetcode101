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
    void addPoints(TreeNode *root, vector<int> *points)
    {
        points->push_back(root->val);
        if (root->left != nullptr)
        {
            addPoints(root->left, points);
        }
        if (root->right != nullptr)
        {
            addPoints(root->right, points);
        }
    }
    vector<vector<int>> closestNodes(TreeNode *root, vector<int> &queries)
    {
        vector<int> points;
        addPoints(root, &points);
        ranges::sort(points);
        int len = points.size();
        vector<vector<int>> result;
        for (auto &q : queries)
        {
            int minmaxindex = ranges::lower_bound(points, q) - points.begin();
            int maxminindex = ranges::lower_bound(points, q + 1) - 1 - points.begin();
            int minval = 0, maxval = 0;
            if (minmaxindex == len)
            {
                maxval = -1;
            }
            else
            {
                maxval = points[minmaxindex];
            }
            if (maxminindex == -1)
            {
                minval = -1;
            }
            else
            {
                minval = points[maxminindex];
            }
            result.push_back({minval, maxval});
        }
        return result;
    }
};

/**
 * 本题其实和tree本身没什么关系。题目中说这是个二叉搜索树，其特点就是非空左枝，非空右枝全部是二叉搜索树，且左边所有值<root<右边所有值。借助这个特点可以得到一个排好序的数组。不借助的话先完全提取出来再sort也是一样的。
 */

class Solution
{
    vector<int> a;

    void dfs(TreeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        dfs(node->left);
        a.push_back(node->val);
        dfs(node->right);
    };

public:
    vector<vector<int>> closestNodes(TreeNode *root, vector<int> &queries)
    {
        dfs(root);
        int n = a.size();
        vector<vector<int>> ans;
        for (int q : queries)
        {
            int j = ranges::lower_bound(a, q) - a.begin();
            int mx = j < n ? a[j] : -1;
            if (j == n || a[j] != q)
            { // a[j]>q, a[j-1]<q
                j--;
            }
            int mn = j >= 0 ? a[j] : -1;
            ans.push_back({mn, mx});
        }
        return ans;
    }
};