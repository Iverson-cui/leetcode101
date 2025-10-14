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
    string frequencySort(string s)
    {
        // first map that counts the frequency of each character
        unordered_map<char, int> counts;
        for (char c : s)
            ++counts[c];
        int len = s.size();
        string result = "";
        // second map that groups characters by their frequency
        unordered_map<int, vector<char>> freqMap;
        for (auto &[ch, freq] : counts)
            freqMap[freq].push_back(ch);
        for (int freq = len; freq >= 0; --freq)
        {
            if (freqMap.count(freq))
            {
                for (char c : freqMap[freq])
                    result.append(freq, c);
            }
        }
        return result;
    }
};

/**
 * 这个题也是利用桶排序，单独维护一个unordered_map数据结构来记录freq等。
 * 底下是很好的一个解法。相比于上面用2个unordered_map，这里用了一个unordered_map和一个multimap。multimap的好处是可以允许许多有同样key的pairs，比如tree的t和r都有freq=1，如果是普通的map会覆盖，multimap不会。而且multimap是有序排列的。底下的解法使用rbegin()和rend()来反向遍历multimap，这样就可以从高频到低频排列字符了。
 * 另外，底下的解法在构造结果字符串时，使用了string的构造函数string(size_t n, char c)，可以直接构造一个有n个c字符的字符串，这样就不需要再用循环一个个添加字符了。
 */

class Solution
{
public:
    string frequencySort(string s)
    {
        unordered_map<char, int> mp;
        multimap<int, char> r;
        string ss = "";

        for (auto a : s)
            mp[a]++;

        for (auto a : mp)
            r.insert({a.second, a.first});

        for (auto it = r.rbegin(); it != r.rend(); ++it)
            ss += string(it->first, it->second);

        // for(auto it = r.rbegin(); it != r.rend(); ++it){
        //    for (int i = 0; i < it->first; ++i) {
        //           ss += it->second;
        //         }
        // }

        return ss;
    }
};
