#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    // 3 constructors
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    void dfs(vector<string> &res, TreeNode *node, string &path)
    {
        if (!node)
            return;
        if (!node->left && !node->right)
        {
            path += to_string(node->val);
            res.push_back(path);
            path.resize(path.size() - to_string(node->val).size());
            return;
        }
        // left node
        if (node->left)
        {
            path += to_string(node->val) + "->";
            dfs(res, node->left, path);
            path.resize(path.size() - to_string(node->val).size() - 2);
        }
        // right node
        if (node->right)
        {
            path += to_string(node->val) + "->";
            dfs(res, node->right, path);
            path.resize(path.size() - to_string(node->val).size() - 2);
        }
        else
            return;
    }
    vector<string> binaryTreePaths(TreeNode *root)
    {
        vector<string> res;
        string path;
        dfs(res, root, path);
        return res;
    }
};