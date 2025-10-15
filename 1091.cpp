#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    int shortestPathBinaryMatrix(vector<vector<int>> &grid)
    {
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        int n = grid.size();
        int dist = 0;
        // vector<int> dir = {0, 1, 0, -1, 1, 1, -1, -1, -1, 0, 1, -1};
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
            return -1;
        if (n == 1 && grid[0][0] == 0)
            return 1;
        q.push({0, 0});
        visited[0][0] = true;
        while (!q.empty())
        {
            ++dist;
            int this_dist_count = q.size();
            int count = 0;
            while (this_dist_count--)
            {
                auto [x, y] = q.front();
                q.pop();
                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < n && !visited[x + dx][y + dy] && grid[x + dx][y + dy] == 0)
                        {
                            if (x + dx == n - 1 && y + dy == n - 1)
                                return dist + 1;
                            q.push({x + dx, y + dy});
                            visited[x + dx][y + dy] = true;
                            ++count;
                        }
                    }
                }
            }
            this_dist_count = count;
        }
        return -1;
    }
};

/**
 * 对于广度优先搜索算法，一般应用在最短距离的情况下。对于可达性问题，深度优先广度优先都可以找到路径。相比于深度优先，不需要搜索所有路径。和深度优先的区别在于，不使用stack而是queue，queue是个FIFO的结构，实现广度优先。
 * 广度优先搜索同样需要一个visited矩阵。避免重复搜索。
 *
 */