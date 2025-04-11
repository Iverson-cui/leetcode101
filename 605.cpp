#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

bool canPlaceFlowers(vector<int> &flowerbed, int n)
{
    int len = flowerbed.size();
    for (int i = 0; i < len; i++)
    {
        int left, right;
        if (flowerbed[i] == 0)
        {

            if ((i == 0) || (flowerbed[i - 1] == 0))
            {
                left = 1;
            }
            else
            {
                left = 0;
            }
            if ((i == len - 1) || (flowerbed[i + 1] == 0))
            {
                right = 1;
            }
            else
            {
                right = 0;
            }
            if (left == 1 && right == 1)
            {
                n--;
                flowerbed[i] = 1;
            }
        }
    }
    return n <= 0;
}

/*
贪心算法，先考虑局部的情况。从第一个花开始遍历，每次只看当前花两侧能不能重，能就种上。
*/