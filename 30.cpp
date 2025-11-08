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
    void oneSlidingWindow(vector<int> &result, string s, vector<string> &words, int &wordLen, int &wordNum, int &windowIndex, int &sLen, unordered_map<string, int> freqWords)
    {
        for (int i = windowIndex; i < sLen; i = i + wordLen)
        {
            --freqWords[s.substr(i, wordLen)];
            if (freqWords[s.substr(i, wordLen)] == 0)
            {
                freqWords.erase(s.substr(i, wordLen));
            }
            if (i < windowIndex + wordLen * wordNum - wordLen)
            {
                continue;
            }
            if (freqWords.empty())
            {
                result.push_back(i - wordLen * (wordNum - 1));
            }
            ++freqWords[s.substr(i - wordLen * (wordNum - 1), wordLen)];
            if (freqWords[s.substr(i - wordLen * (wordNum - 1), wordLen)] == 0)
            {
                freqWords.erase(s.substr(i - wordLen * (wordNum - 1), wordLen));
            }
        }
    }
    vector<int> findSubstring(string s, vector<string> &words)
    {
        vector<int> result;
        int wordNum = words.size();
        int wordLen = words[0].size();
        int sLen = s.size();
        if (sLen < wordLen * wordNum)
        {
            return result;
        }
        unordered_map<string, int> freqWords;
        for (string word : words)
        {
            ++freqWords[word];
        }
        for (int i = 0; i < wordLen; ++i)
        {
            oneSlidingWindow(result, s, words, wordLen, wordNum, i, sLen, freqWords);
        }
        return result;
    }
};

class Solution
{
public:
    vector<int> findSubstring(string &s, vector<string> &words)
    {
        vector<int> res; // 结果集
        // 拿到各个长度
        int m = words.size(), n = words[0].size(), ls = s.size();

        // 开始外层循环，此处注意循环条件：i<n
        for (int i = 0; i < n && i + m * n <= ls; ++i)
        {
            unordered_map<string, int> differ; // 这就是上面说的哈希表
            // 第一个窗口，看看s被窗口框到的有哪些单词，哈希表对应单词的数量++，
            // 这两个for主要是用来初始化滑动窗口，现在只是框住了，还没开始滑
            for (int j = 0; j < m; ++j)
            {
                ++differ[s.substr(i + j * n, n)];
            }
            // 遍历words，哈希表对应单词数量--，对应单词数量为0时删除单词
            for (string &word : words)
            {
                if (--differ[word] == 0)
                {
                    differ.erase(word);
                }
            }
            // 内层循环：从i开始滑了，每次滑动一个单词的长度n，窗口一路滑到尾
            for (int start = i; start < ls - m * n + 1; start += n)
            {
                // 第一个窗口已经加减过了，所以start==i的时候直接到下面去判断满不满足就行了
                if (start != i)
                {
                    // word就是窗口最右侧的那个单词，也就是新进入窗口的单词，要++
                    string word = s.substr(start + (m - 1) * n, n);
                    if (++differ[word] == 0)
                    { // 判断单词值是不是0，是就删除单词
                        differ.erase(word);
                    }
                    // word是窗口左侧离开的单词，要--
                    word = s.substr(start - n, n);
                    if (--differ[word] == 0)
                    { // 判断单词值是不是0，是就删除单词
                        differ.erase(word);
                    }
                }
                // 判断哈希表是否为空，如果是，条件符合，窗口起始下标放进结果集
                if (differ.empty())
                {
                    res.emplace_back(start);
                }
            }
        }
        return res;
    }
};

/**
 * 几个题解的思路都类似，这个题和其余不同的地方在于词可以从任意index的char开始算，即假如word len=4，则0，4，8是一组，1，5，9是一组，2，6，10是一组，3，7，11是一组。所以针对每一组，对string s进行分割，都要进行一次滑动窗口，总共是四次。
 * 统计的时候，可以采用这里unordered_map<string, int>，记录了diff，vector里++，窗口里出现就--，如果empty就是合理解。
 */