#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

class Solution
{
public:
    int f(const string &s)
    {
        int maxCount = 0;
        int minChar = s[0];
        for (auto ch : s)
        {
            if (ch < minChar)
            {
                minChar = ch;
                maxCount = 1;
            }
            else if (ch == minChar)
            {
                maxCount++;
            }
        }
        return maxCount;
    }
    vector<int> numSmallerByFrequency(vector<string> &queries, vector<string> &words)
    {
        vector<int> wordFreq;
        for (const auto &word : words)
        {
            wordFreq.push_back(f(word));
        }
        vector<int> result;
        ranges::sort(wordFreq);
        for (const auto &query : queries)
        {
            int currentCount = f(query);
            result.push_back(wordFreq.end() - ranges::lower_bound(wordFreq, currentCount + 1));
        }
        return result;
    }
};