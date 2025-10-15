#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution
{
public:
    void backtrack(vector<vector<string>> &res, vector<string> &board, int row, vector<bool> &col, vector<bool> &ldiag, vector<bool> &rdiag, int n)
    {
        for (int i = 0; i < n; ++i)
        {
            if (col[i] || ldiag[n - row + i - 1] || rdiag[row + i])
                continue;
            if (row == n - 1)
            {
                board[row][i] = 'Q';
                res.push_back(board);
                board[row][i] = '.';
                return;
            }
            board[row][i] = 'Q';
            col[i] = true;
            ldiag[n - row + i - 1] = true;
            rdiag[row + i] = true;
            backtrack(res, board, row + 1, col, ldiag, rdiag, n);
            board[row][i] = '.';
            col[i] = false;
            ldiag[n - row + i - 1] = false;
            rdiag[row + i] = false;
        }
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> res;
        vector<string> board(n, string(n, '.'));
        vector<bool> col(n, false);
        vector<bool> ldiag(2 * n - 1, false); // r + c
        vector<bool> rdiag(2 * n - 1, false); // r - c + n - 1
        backtrack(res, board, 0, col, ldiag, rdiag, n);
        return res;
    }
};

/**
 * 先读明白题。N皇后问题，棋子的摆放必须使得每一行有且仅有一个棋子。初始思路是维护4个矩阵，分别对应行，列，左斜，右斜的情况。如果按照行去遍历，就不需要行矩阵了。
 * 解题的思路仍然按照回溯和递归的方法。先按照行遍历，假设当前行的某一列放置了棋子，那么就把对应的列，左斜，右斜矩阵对应位置设置为true。然后递归调用下一行的函数。调用完再更改回去。
 */