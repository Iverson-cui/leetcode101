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
    int maxRepOpt1(string text)
    {
        unordered_map<char, int> totalCount;
        int len = text.size();
        for (char c : text)
        {
            totalCount[c]++;
        }
        int maxLength = 1;
        // update parameters
        int diffCharCount = 0;
        char currentChar = text[0];
        int left = 0, right = 0;
        int diffIndex = 0;
        for (; right < len; ++right)
        {
            printf("left=%d, right=%d, currentChar=%c\n", left, right, currentChar);
            if (text[right] != currentChar)
            {
                diffCharCount++;
                if (diffCharCount == 1)
                {
                    diffIndex = right;
                }
            }
            if (diffCharCount > 1)
            {
                maxLength = max(maxLength, min(right - left, totalCount[currentChar]));
                left = diffIndex;
                right = diffIndex;
                diffCharCount = 0;
                currentChar = text[right];
                printf("Reset: left=%d, right=%d, currentChar=%c\n", left, right, currentChar);
                printf("current maxLength=%d\n", maxLength);
            }
        }
        if (diffCharCount == 1)
        {
            maxLength = max(maxLength, min(right - left, totalCount[currentChar]));
        }
        else
        {
            maxLength = max(maxLength, min(right - left + 1, totalCount[currentChar]));
        }
        printf("final left=%d final right=%d final maxLength=%d\n", left, right, maxLength);
        return maxLength;
    }
};

int main()
{
    Solution sol;
    string text = "aabbaba";
    cout << sol.maxRepOpt1(text) << endl; // Output should be 4
    return 0;
}

/**
 * 因为只能替换一次，所以下面的解法直接hard code来处理中间有一个不一样字符的情况。
 */

class Solution
{
public:
    int maxRepOpt1(string text)
    {
        int cnt[26] = {0};
        for (char &c : text)
        {
            ++cnt[c - 'a'];
        }
        int n = text.size();
        int ans = 0, i = 0;
        while (i < n)
        {
            int j = i;
            while (j < n && text[j] == text[i])
            {
                ++j;
            }
            int l = j - i;
            int k = j + 1;
            while (k < n && text[k] == text[i])
            {
                ++k;
            }
            int r = k - j - 1;
            ans = max(ans, min(l + r + 1, cnt[text[i] - 'a']));
            i = j;
        }
        return ans;
    }
};