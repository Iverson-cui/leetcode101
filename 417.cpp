#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        int row = heights.size();
        int col = heights[0].size();
        vector<vector<int>> res;
        vector<int> dir = {-1, 0, 1, 0, -1};
        stack<pair<int, int>> stk;
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                bool pacific = false, atlantic = false;
                stk.push({i, j});
                while (!stk.empty())
                {
                    auto cur = stk.top();
                    stk.pop();
                    int r = cur.first, c = cur.second;
                    if (r == 0 || c == 0)
                        pacific = true;
                    if (r == row - 1 || c == col - 1)
                        atlantic = true;
                    if (pacific && atlantic)
                    {
                        break;
                    }
                    for (int d = 0; d < 4; ++d)
                    {
                        if (r + dir[d] >= 0 && r + dir[d] < row && c + dir[d + 1] >= 0 && c + dir[d + 1] < col && heights[r + dir[d]][c + dir[d + 1]] <= heights[r][c])
                        {
                            stk.push({r + dir[d], c + dir[d + 1]});
                        }
                    }
                }
                if (pacific && atlantic)
                {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }
};

/**
 * 以上的解法就是简单的stack-based DFS，在这个题里，超时。因为需要遍历的情况太多了。和前面的相邻岛屿问题不同，这里面所有符合条件的路径都必须经过矩阵的最外层元素，所以不如直接从最外层元素为起点，反着思考，让水往高处流，减少了许多不必要的情况。
 * 以下就是采用这个思路的stack的方法。
 */

class Solution
{
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        int row = heights.size();
        int col = heights[0].size();
        // bool matrix to record if can reach Atlantic or Pacific
        vector<vector<bool>> At(row, vector<bool>(col, false));
        vector<vector<bool>> Pa(row, vector<bool>(col, false));
        vector<vector<int>> res;
        vector<int> dir = {-1, 0, 1, 0, -1};
        stack<pair<int, int>> stk_pa, stk_at;

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                // pa
                if (i == 0 || j == 0)
                {
                    stk_pa.push({i, j});
                    Pa[i][j] = true;
                    while (!stk_pa.empty())
                    {
                        auto cor = stk_pa.top();
                        stk_pa.pop();
                        int r = cor.first, c = cor.second;
                        for (int d = 0; d < 4; ++d)
                        {
                            if (r + dir[d] >= 0 && r + dir[d] < row && c + dir[d + 1] >= 0 && c + dir[d + 1] < col && heights[r + dir[d]][c + dir[d + 1]] >= heights[r][c] && !Pa[r + dir[d]][c + dir[d + 1]])
                            {
                                stk_pa.push({r + dir[d], c + dir[d + 1]});
                                Pa[r + dir[d]][c + dir[d + 1]] = true;
                            }
                        }
                    }
                }
                // at
                if (i == row - 1 || j == col - 1)
                {
                    stk_at.push({i, j});
                    At[i][j] = true;
                    while (!stk_at.empty())
                    {
                        auto cor = stk_at.top();
                        stk_at.pop();
                        int r = cor.first, c = cor.second;
                        for (int d = 0; d < 4; ++d)
                        {
                            if (r + dir[d] >= 0 && r + dir[d] < row && c + dir[d + 1] >= 0 && c + dir[d + 1] < col && heights[r + dir[d]][c + dir[d + 1]] >= heights[r][c] && !At[r + dir[d]][c + dir[d + 1]])
                            {
                                stk_at.push({r + dir[d], c + dir[d + 1]});
                                At[r + dir[d]][c + dir[d + 1]] = true;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (At[i][j] && Pa[i][j])
                {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }
};

/**
 * 以上的解法是stack-based DFS，下面是recursion-based DFS。
 */

class Solution
{
public:
    vector<int> dir = {-1, 0, 1, 0, -1};
    void isConnected(vector<vector<int>> &heights, vector<vector<bool>> &visited, int i, int j)
    {
        if (visited[i][j])
            return;
        visited[i][j] = true;
        int row = heights.size();
        int col = heights[0].size();

        for (int d = 0; d < 4; ++d)
        {
            if (i + dir[d] >= 0 && i + dir[d] < row && j + dir[d + 1] >= 0 && j + dir[d + 1] < col && heights[i + dir[d]][j + dir[d + 1]] >= heights[i][j] && !visited[i + dir[d]][j + dir[d + 1]])
            {
                isConnected(heights, visited, i + dir[d], j + dir[d + 1]);
            }
        }
    }
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        int row = heights.size();
        int col = heights[0].size();
        // bool matrix to record if can reach Atlantic or Pacific
        vector<vector<bool>> At(row, vector<bool>(col, false));
        vector<vector<bool>> Pa(row, vector<bool>(col, false));
        vector<vector<int>> res;
        // vector<int> dir = {-1, 0, 1, 0, -1};
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                // pa
                if (i == 0 || j == 0)
                {
                    if (!Pa[i][j])
                    {
                        isConnected(heights, Pa, i, j);
                    }
                }
                // at
                if (i == row - 1 || j == col - 1)
                {
                    if (!At[i][j])
                    {
                        isConnected(heights, At, i, j);
                    }
                }
            }
        }
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (At[i][j] && Pa[i][j])
                {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }
};