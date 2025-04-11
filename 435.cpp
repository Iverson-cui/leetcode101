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

int eraseOverlapIntervals(vector<vector<int>> &intervals)
{
    sort(intervals.begin(), intervals.end(),
         [](vector<int> &a, vector<int> &b)
         { return a[1] < b[1]; });
    int removed = 0, prev_end = intervals[0][1];
    for (int i = 1; i < intervals.size(); ++i)
    {
        if (intervals[i][0] < prev_end)
        {
            ++removed;
        }
        else
        {
            prev_end = intervals[i][1];
        }
    }
    return removed;
};

int main(void)
{

    return 0;
}

/*
贪心算法，先排序，后遍历。排序的原则是后边界的大小。按照后边界从小到大的顺序排序每排列完之后仍然用贪心，考虑当前的interval和前一个interval的关系，很局部的角度。
如果当前interval的start比前一个interval的end小，说明有重叠，删除一个interval。否则，更新前一个interval的end为当前interval的end。
*/