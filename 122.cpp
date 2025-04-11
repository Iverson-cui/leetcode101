#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int maxProfit(vector<int> &prices)
{
    int profit = 0;
    int len = prices.size();
    // hold = 0 if not hold any stock, 1 if hold the stock
    // int hold = 0;
    for (int i = 0; i < len - 1; i++)
    {
        if (prices[i] <= prices[i + 1])
        {
            // if (hold == 0)
            // {
            //     hold = 1;
            // }
            profit += prices[i + 1] - prices[i];
        }
        // else
        // {
        //     hold = 0;
        // }
    }
    return profit;
}
/*
先确定购买模式。当价格上升的时候买 挣上升钱。下降的时候卖出去。模式确定了，直接计算一共上升了多少就可以了。　
*/