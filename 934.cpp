#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    int shortestBridge(vector<vector<int>> &grid)
    {
        vector<int> dir = {1, 0, -1, 0, 1};
        int rows = grid.size();
        int cols = grid[0].size();
        // find 1st island by DFS
        stack<pair<int, int>> stk_1_island;
        // find 2nd island by BFS
        queue<pair<int, int>> q_2_island;
        bool found = false;
        for (int i = 0; i < rows && !found; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (grid[i][j] == 1)
                {
                    stk_1_island.push({i, j});
                    grid[i][j] = 2; // 1st island mark as visited as 2
                    while (!stk_1_island.empty())
                    {
                        auto [x, y] = stk_1_island.top();
                        stk_1_island.pop();
                        for (int d = 0; d < 4; ++d)
                        {
                            int nx = x + dir[d];
                            int ny = y + dir[d + 1];
                            // belongs to 1st island
                            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 1)
                            {
                                stk_1_island.push({nx, ny});
                                grid[nx][ny] = 2; // mark as visited
                            }
                            // belongs to adjacent shore
                            else if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 0)
                            {
                                // adjacent to the first island, add to queue for BFS
                                q_2_island.push({nx, ny});
                                grid[nx][ny] = -1; // mark as visited
                            }
                        }
                    }
                    found = true;
                    break;
                }
            }
        }
        int dist = 1;
        while (!q_2_island.empty())
        {
            int this_dist_count = q_2_island.size();
            while (this_dist_count--)
            {
                auto [x, y] = q_2_island.front();
                q_2_island.pop();
                for (int d = 0; d < 4; ++d)
                {
                    int nx = x + dir[d];
                    int ny = y + dir[d + 1];
                    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols)
                    {
                        if (grid[nx][ny] == 1)
                        {
                            return dist;
                        }
                        else if (grid[nx][ny] == 0)
                        {
                            q_2_island.push({nx, ny});
                            grid[nx][ny] = -1; // mark as visited
                        }
                    }
                }
            }
            ++dist;
        }
        return -1;
    }
};