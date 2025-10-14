#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    vector<int> dir = {0, 1, 0, -1, 0};
    bool search(vector<vector<char>> &board, string &word, vector<vector<bool>> &visited, int i, int j, int index)
    {
        int m = board.size();
        auto n = board[0].size();
        if (index == word.size() - 1)
            return true;

        for (int d = 0; d < 4; ++d)
        {
            int x = i + dir[d];
            int y = j + dir[d + 1];
            if (x >= 0 && x < m && y >= 0 && y < n && !visited[x][y] && board[x][y] == word[index + 1])
            {
                visited[x][y] = true;
                if (search(board, word, visited, x, y, index + 1))
                    return true;
                visited[x][y] = false;
            }
        }
        return false;
    }
    bool exist(vector<vector<char>> &board, string word)
    {
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == word[0])
                {
                    visited[i][j] = true;
                    if (search(board, word, visited, i, j, 0))
                        return true;
                    visited[i][j] = false;
                }
            }
        }
        return false;
    }
};

/**
 * 仍然使用回溯法，先假设按照某条路径走，就把visited矩阵对应的元素设置为True，走完了需要回调为False
 */