#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    void dfs(vector<vector<int>> &isConnected, vector<bool> &visited, int i)
    {
        // mark it as visited
        visited[i] = true;
        for (int j = 0; j < isConnected.size(); ++j)
        {
            if (isConnected[i][j] == 1 && !visited[j])
            {
                dfs(isConnected, visited, j);
            }
        }
    }

    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                dfs(isConnected, visited, i);
                provinces++;
            }
        }
        return provinces;
    }
};

/**
 * 这个题和695题的最大区别在于695，对于每个矩阵里的元素需要看它的上下左右四个方向，而这里，每个城市可以和n个城市中的任意一个进行相连。在695里，2个相连意思是该方向上为1，在这里相连意思是第i行的第j列的元素为1。
 * 此类搜索题，不管是DFS还是BFS，都是类似的套路。重点是弄清楚要搜索的范围是什么，如何处理搜索到的情况。
 * 同样可以用stack或递归来做DFS。上面是递归，下面是stack。
 */

class Solution
{
public:
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;
        stack<int> s;
        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                s.push(i);
                visited[i] = true;
                while (!s.empty())
                {
                    auto t = s.top();
                    s.pop();
                    for (int j = 0; j < n; ++j)
                    {
                        if (isConnected[t][j] == 1 && !visited[j])
                        {
                            s.push(j);
                            visited[j] = true;
                        }
                    }
                }
                provinces++;
            }
        }
        return provinces;
    };
};