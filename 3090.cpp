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
    int maximumLengthSubstring(string s)
    {
        int len = s.length();
        int left = 0, right = 0;
        int maxLen = 0;
        // unordered_map<char, int> charFreqMap;
        int cnt[26]{0};
        for (; right < len; ++right)
        {
            if (cnt[s[right] - 'a'] > 1)
            {
                maxLen = max(maxLen, right - left);
                while (left < right && cnt[s[right] - 'a'] > 1)
                {
                    cnt[s[left] - 'a']--;
                    left++;
                }
            }
            cnt[s[right] - 'a']++;
        }
        return max(maxLen, right - left);
    }
};

/**
 * 因为一共就26个字母，所以可以用array代替hash map来存储字符频次，从而节省空间和时间开销。int cnt[26] 意思是size是26的，每个size都装int的array，初始化为0。
 */