#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution
{
public:
    void DFS(vector<vector<char>> &board, int i, int j, int m, int n)
    {
        if (i < 0 or j < 0 or i >= m or j >= n or board[i][j] != 'O')
            return;
        board[i][j] = '#';
        DFS(board, i - 1, j, m, n);
        DFS(board, i + 1, j, m, n);
        DFS(board, i, j - 1, m, n);
        DFS(board, i, j + 1, m, n);
    }

    void solve(vector<vector<char>> &board)
    {

        // We will use boundary DFS to solve this problem

        // Let's analyze when an 'O' cannot be flipped,
        // if it has atleast one 'O' in it's adjacent, AND ultimately this chain of adjacent 'O's is connected to some 'O' which lies on boundary of board

        // consider these two cases for clarity :
        /*
          O's won't be flipped          O's will be flipped
          [X O X X X]                   [X X X X X]
          [X O O O X]                   [X O O O X]
          [X O X X X]                   [X O X X X]
          [X X X X X]                   [X X X X X]

        So we can conclude if a chain of adjacent O's is connected some O on boundary then they cannot be flipped

        */

        // Steps to Solve :
        // 1. Move over the boundary of board, and find O's
        // 2. Every time we find an O, perform DFS from it's position
        // 3. In DFS convert all 'O' to '#'      (why?? so that we can differentiate which 'O' can be flipped and which cannot be)
        // 4. After all DFSs have been performed, board contains three elements,#,O and X
        // 5. 'O' are left over elements which are not connected to any boundary O, so flip them to 'X'
        // 6. '#' are elements which cannot be flipped to 'X', so flip them back to 'O'
        // 7. finally, Upvote the solution😊

        int m = board.size();

        if (m == 0)
            return;

        int n = board[0].size();

        // Moving over firts and last column
        for (int i = 0; i < m; i++)
        {
            if (board[i][0] == 'O')
                DFS(board, i, 0, m, n);
            if (board[i][n - 1] == 'O')
                DFS(board, i, n - 1, m, n);
        }

        // Moving over first and last row
        for (int j = 0; j < n; j++)
        {
            if (board[0][j] == 'O')
                DFS(board, 0, j, m, n);
            if (board[m - 1][j] == 'O')
                DFS(board, m - 1, j, m, n);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                if (board[i][j] == '#')
                    board[i][j] = 'O';
            }
    }
};

/**
 * 关键在于读懂题。首先一个元素的上下左右算做connect，其次，一个或多个相互connect的O元素算做一个region。一个region is surrounded with X cells当且仅当这个region的所有O元素都不在边界上且region的周围都是X。后者很容易满足，前者需要判断。所以题干的本质就是找那些不延伸到边界的O。只要不包括边界，任何region，不管是1个O还是多个O，都要变成X。
 * 所以更快捷的方法是从边界出发，执行BFS。任何这样找到的都是不能翻转的。我们原地将其更改为#。而可以翻转的O最终会留在board上。最后再遍历一遍board，将O翻转为X，将#翻转为O即可。
 * 创新点在于：1.从原地更改而记录状态，避免额外空间开销；2.从边界出发，避免了对所有O的判断。
 */