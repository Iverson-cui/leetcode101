#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

bool compareByDifference(const vector<int> &a,
                         const vector<int> &b)
{
    return (a[1]) < (b[1]);
}

int findMinArrowShots(vector<vector<int>> &points)
{
    sort(points.begin(), points.end(), compareByDifference);
    int len = points.size();
    int num = len;
    for (int i = 1; i < len; i++)
    {
        if ((points[i][0]) <= points[i - 1][1])
        {
            // find one overlapping intervals, num--
            num--;
            points[i][1] = points[i - 1][1];
        }
    }
    return num;
}

/*
本质还是贪心，和重叠区间一样，先按照末尾的大小排序。先默认每个气球都有一根，之后每当i的开始小于i-1的结束的时候就少射一根。注意：这个时候这根箭射的位置就有具体的区间了。在判断下一个气球的时候就要判断他的开始是否小于这个新的更小的区间的上界。这个比较区间的更新是435没有的。
*/