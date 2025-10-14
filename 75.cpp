#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        unordered_map<int, int> counts;
        for (int v : nums)
            ++counts[v];
        multimap<int, int> freqMap;
        for (auto &[num, freq] : counts)
            freqMap.insert({num, freq});
        int idx = 0;
        for (auto &entry : freqMap)
        {
            int num = entry.first;
            int freq = entry.second;
            for (int k = 0; k < freq && idx < (int)nums.size(); ++k)
                nums[idx++] = num;
        }
    }
};

/**
 * 荷兰国旗问题，上面的桶排序法+unordered_map+multimap的方法确实可以。相比直接用map的方法最大好处就是快，因为unordered_map的底层是hash table而其余2个map的底层是binary tree。
 * 还有种三指针解法：https://leetcode.com/problems/sort-colors/solutions/6751648/dutch-national-flag-algorithm-with-images-example-walkthrough-c-python-java/
 */