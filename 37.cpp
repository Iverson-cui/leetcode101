#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
public:
    bool isValid(vector<vector<char>> &board, int row, int col, char c)
    {
        // row
        for (int j = 0; j < 9; ++j)
        {
            if (board[row][j] == c)
            {
                return false;
            }
        }
        // column
        for (int i = 0; i < 9; ++i)
        {
            if (board[i][col] == c)
            {
                return false;
            }
        }
        // 3*3 box
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; ++i)
        {
            for (int j = startCol; j < startCol + 3; ++j)
            {
                if (board[i][j] == c)
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool recursive(vector<vector<char>> &board, int row, int col)
    {
        // bool solved = false;
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (board[i][j] != '.')
                {
                    continue;
                }
                for (char c = '1'; c <= '9'; ++c)
                {
                    if (isValid(board, i, j, c))
                    {
                        board[i][j] = c;
                        if (recursive(board, row, col))
                        {
                            return true;
                        }
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>> &board)
    {
        int num_row = board.size();
        int num_col = board[0].size();
        recursive(board, num_row, num_col);
    }
};