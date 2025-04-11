#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

vector<int> partitionLabels(string s)
{
    // index means the last occurance of each character.
    vector<int> index(26, 0);
    int strlen = s.length();
    for (int i = 0; i < strlen; i++)
    {
        index[s[i] - 'a'] = i;
    }
    vector<int> result;
    int start = 0;
    int end = 0;
    for (int i = 0; i < strlen; i++)
    {
        end = index[s[i] - 'a'] > end ? index[s[i] - 'a'] : end;
        if (i == end)
        {
            result.push_back(end - start + 1);
            start = end + 1;
        }
    }
    return result;
}

/*
先记录26个字母每个字母在字符串中出现的最晚位置。当前字符串的分割点在于其中所含的所有字母中最晚位置最晚的那个。
*/