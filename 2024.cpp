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
    int singleSlidingWindow(string &answer_key, int &k, char ch, int &len)
    {
        int maxLen = 0;
        int left = 0, right = 0;
        int count = 0;
        bool has = false;
        for (; right < len; ++right)
        {
            if ((!has) && (answer_key[right] == ch) && (count < k))
            {
                ++count;
                if (count == k)
                {
                    has = true;
                }
            }
            else if (answer_key[right] == ch && has)
            {
                while (answer_key[left] != ch)
                {
                    ++left;
                }
                ++left;
            }
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
    int maxConsecutiveAnswers(string answerKey, int k)
    {
        int len = answerKey.size();
        int left = 0, right = 0;
        int maxLen = 0;
        maxLen = max(singleSlidingWindow(answerKey, k, 'T', len), singleSlidingWindow(answerKey, k, 'F', len));
        return maxLen;
    }
};