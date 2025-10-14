#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int max_area = 0;
        stack<pair<int, int>> stk;
        int rows = grid.size();
        int cols = grid[0].size();
        vector<int> dir = {-1, 0, 1, 0, -1}; // 4 directions
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (grid[i][j] == 1)
                {
                    int area = 0;
                    // push (i,j) in stk
                    stk.push({i, j});
                    grid[i][j] = 0; // mark as visited
                    while (!stk.empty())
                    {
                        auto [x, y] = stk.top();

                        ++area;
                        stk.pop();
                        for (int d = 0; d < 4; ++d)
                        {
                            // if neighbor does exist and neighbor is 1
                            if (x + dir[d] >= 0 && x + dir[d] < rows && y + dir[d + 1] >= 0 && y + dir[d + 1] < cols && grid[x + dir[d]][y + dir[d + 1]] == 1)
                            {
                                stk.push({x + dir[d], y + dir[d + 1]});
                                grid[x + dir[d]][y + dir[d + 1]] = 0; // mark as visited
                            }
                        }
                    }
                    max_area = max(max_area, area);
                }
            }
        };
        return max_area;
    }
};

/**
 * 以上是用DFS深度优先的写法。注意在写的时候要妥善处理好边界问题，有的时候current元素的周围4个元素不一定都存在。同时处理好什么时候mark as visited，什么时候update area的问题。
 * 这个问题也可以用递归的写法,见下面。
 */
class Solution
{
public:
    int dfs(pair<int, int> pos, vector<vector<int>> &grid)
    {
        // if current pos is 0
        // vector<int> dir = {-1, 0, 1, 0, -1};
        if (pos.first < 0 || pos.first >= (int)grid.size() || pos.second < 0 || pos.second >= (int)grid[0].size() || grid[pos.first][pos.second] == 0)
            return 0;
        else
        {

            grid[pos.first][pos.second] = 0; // mark as visited
            return 1 + dfs({pos.first - 1, pos.second}, grid) + dfs({pos.first + 1, pos.second}, grid) + dfs({pos.first, pos.second - 1}, grid) + dfs({pos.first, pos.second + 1}, grid);
        }
    }
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int max_area = 0;
        for (int i = 0; i < (int)grid.size(); ++i)
        {
            for (int j = 0; j < (int)grid[0].size(); ++j)
            {
                if (grid[i][j] == 1)
                {
                    int area = dfs({i, j}, grid);
                    max_area = max(max_area, area);
                }
            }
        };
        return max_area;
    }
};