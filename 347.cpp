#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        // number to frequency
        unordered_map<int, int> counts;
        for (int num : nums)
        {
            ++counts[num];
        }

        // frequency to ints with that frequency
        unordered_map<int, vector<int>> buckets;

        for (auto &pair : counts)
        {
            int num = pair.first;
            int freq = pair.second;
            // for unordered_map, if key not exist, it will create a new entry
            buckets[freq].push_back(num);
        }

        int vector_len = nums.size();
        vector<int> top_k;
        // freq max is vector_len
        for (int cur = vector_len; cur >= 0; --cur)
        {
            // given a freq, there are numbers with that freq
            if (buckets.count(cur))
            {
                top_k.insert(top_k.end(), buckets[cur].begin(), buckets[cur].end());
                if (k > buckets[cur].size())
                {
                    k = k - buckets[cur].size();
                }
                else
                {
                    return top_k;
                }
            }
        }
        return top_k;
    }
};

/**
 * 桶排序，其实很简单。因为在这个题里，要找到最frequently appeared element，而不检索整个array就不知道谁更frequent。所以维持一个dict（在C++里是unordered_map），记录每个数字出现的频率。但是unordered_map的缺点是无序的，好处是查找时间很快。所以直接从freq高到低无法实现，我们只能从高到低遍历所有可能的freq（0到n），然后看在buckets里有没有这个freq的entry，如果有，就把这些数字都放到结果里，直到结果长度达到k。
 */