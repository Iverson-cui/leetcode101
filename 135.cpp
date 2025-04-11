#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int candy(vector<int> &ratings)
{
    int size = ratings.size();
    vector<int> candy(size, 1);
    for (int i = 0; i < size - 1; i++)
    {
        // from left to right
        if (ratings.at(i) < ratings.at(i + 1))
        {
            candy.at(i + 1) = candy.at(i) + 1;
        }
    }
    for (int i = size - 1; i > 0; i--)
    {

        if (ratings.at(i) < ratings.at(i - 1))
        {
            candy.at(i - 1) = max(candy.at(i - 1), candy.at(i) + 1);
        }
    }
    return accumulate(candy.begin(), candy.end(), 0);
}

/*
每个孩子两侧的孩子的情况都要考虑。也是贪心先考虑局部，先一个循环考虑一侧，再一个循环考虑另一侧。如果大就加一。
*/