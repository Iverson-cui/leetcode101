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
    int singleSlidingWindow(string s, int windowSize, int k)
    {
        int result = 0;
        int len = s.size();
        unordered_map<char, int> charCount;
        int satisfiedChar = 0;
        int targetSatisfiedChar = windowSize / k;
        int accumulate = 0;
        for (int i = 0; i < len; ++i)
        {
            if (i > 0)
            {
                // printf("s[%d]-s[%d]=%d\n", i, i - 1, s[i] - s[i - 1]);
                if ((s[i] - s[i - 1] > 2) && (windowSize > 1))
                {
                    charCount.clear();
                    // each time diff is bigger than 2, reset accumulate.
                    accumulate = windowSize;
                    // printf("when i=%d, reset accumulate to %d\n", i, accumulate);
                    satisfiedChar = 0;
                }
            }
            charCount[s[i]]++;
            if (charCount[s[i]] == k)
            {
                ++satisfiedChar;
            }
            else if (charCount[s[i]] == k + 1)
            {
                --satisfiedChar;
            }
            if (accumulate > 0)
            {
                --accumulate;
                if (accumulate == 0)
                {
                    if (satisfiedChar == targetSatisfiedChar)
                    {
                        // printf("i=%d, window=%s\n", i, s.substr(0, i + 1).c_str());
                        // printf("  accumulate=%d\n", accumulate);
                        ++result;
                    }
                }
                continue;
            }
            if (i < windowSize)
            {
                if (satisfiedChar == targetSatisfiedChar)
                {
                    // printf("i=%d, window=%s\n", i, s.substr(0, i + 1).c_str());
                    // printf("  accumulate=%d\n", accumulate);
                    ++result;
                }
                continue;
            }
            --charCount[s[i - windowSize]];
            if (charCount[s[i - windowSize]] == k)
            {
                ++satisfiedChar;
            }
            else if (charCount[s[i - windowSize]] == k - 1)
            {
                --satisfiedChar;
            }
            if (satisfiedChar == targetSatisfiedChar)
            {
                // printf("i=%d, window=%s\n", i, s.substr(i - windowSize + 1, windowSize).c_str());
                ++result;
            }
        }
        // printf("Window Size %d: %d\n", windowSize, result);
        return result;
    }
    int countCompleteSubstrings(string word, int k)
    {
        int result = 0;
        int len = word.size();
        for (int windowSize = k; windowSize <= len; windowSize += k)
        {
            result += singleSlidingWindow(word, windowSize, k);
        }
        return result;
    }
};

int main(void)
{
    Solution sol;
    string word = "jjjqq";
    int k = 1;
    int result = sol.countCompleteSubstrings(word, k);
    cout << "Result: " << result << endl;
    return 0;
}

/**
 * 上面的解法过于麻烦，引入accumulate是为了处理相邻char相差大于2的情况，更方便的做法是直接根据相差大于2的字符来将字符串分段处理。
 * 注意这里面string_view数据结构的使用，其实他类似于string temp=string.substr(start, length)，但是不会进行数据拷贝，节省时间和空间，本质上是个指针。
 * 相比用一个unordered_map来记录char出现的频率，因为char本身只有26个，所以直接用array更好。检验一个窗口是否合法，就看array的各个数。一个字符要么出现0次，要么出现k次，其余情况全是不合法的。
 */

class Solution
{
    int f(string_view s, int k)
    {
        int res = 0;
        // try all possible number of unique characters
        for (int m = 1; m <= 26 && k * m <= s.length(); m++)
        {
            int cnt[26]{};
            // lambda function to check validity
            auto check = [&]()
            {
                for (int i = 0; i < 26; i++)
                {
                    // a character appears but not exactly k times->invalid
                    if (cnt[i] && cnt[i] != k)
                    {
                        return;
                    }
                }
                res++;
            };
            // sliding window
            for (int right = 0; right < s.length(); right++)
            {
                cnt[s[right] - 'a']++;
                int left = right + 1 - k * m;
                if (left >= 0)
                {
                    check();
                    cnt[s[left] - 'a']--;
                }
            }
        }
        return res;
    }

public:
    int countCompleteSubstrings(string word, int k)
    {
        int n = word.length();
        int ans = 0;
        string_view s(word); // string_view 的 substr 没有拷贝
        for (int i = 0; i < n;)
        {
            int st = i;
            for (i++; i < n && abs(int(word[i]) - int(word[i - 1])) <= 2; i++)
                ;
            ans += f(s.substr(st, i - st), k);
        }
        return ans;
    }
};