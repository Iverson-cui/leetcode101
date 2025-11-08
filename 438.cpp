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
    vector<int> findAnagrams(string s, string p)
    {
        int shortt = p.size();
        int longg = s.size();
        unordered_map<char, int> freqs;
        unordered_map<char, int> freqp;
        vector<int> result;
        for (char c : p)
        {
            freqp[c]++;
        }
        for (int i = 0; i < longg; ++i)
        {
            freqs[s[i]]++;
            if (i < shortt - 1)
            {
                continue;
            }
            bool temp = true;
            for (auto &pr : freqp)
            {
                if (freqs[pr.first] != pr.second)
                {
                    temp = false;
                    break;
                }
            }
            if (temp)
            {
                result.push_back(i - shortt + 1);
            }
            freqs[s[i - shortt + 1]]--;
            if (freqs[s[i - shortt + 1]] == 0)
            {
                freqs.erase(s[i - shortt + 1]);
            }
        }
        return result;
    }
};

class Solution
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        int shortt = p.size();
        int longg = s.size();
        unordered_map<char, int> freqDiffs;
        // unordered_map<char, int> freqp;
        vector<int> result;
        for (char c : p)
        {
            freqDiffs[c]++;
        }
        for (int i = 0; i < longg; ++i)
        {
            freqDiffs[s[i]]--;
            if (freqDiffs[s[i]] == 0)
            {
                freqDiffs.erase(s[i]);
            }
            if (i < shortt - 1)
            {
                continue;
            }
            if (freqDiffs.empty())
            {
                result.push_back(i - shortt + 1);
            }
            freqDiffs[s[i - shortt + 1]]++;
            if (freqDiffs[s[i - shortt + 1]] == 0)
            {
                freqDiffs.erase(s[i - shortt + 1]);
            }
        }
        return result;
    }
};

class Solution
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        vector<int> ans;
        array<int, 26> cnt_p{}; // 统计 p 的每种字母的出现次数
        array<int, 26> cnt_s{}; // 统计 s 的长为 p.length() 的子串 s' 的每种字母的出现次数
        for (char c : p)
        {
            cnt_p[c - 'a']++;
        }
        for (int right = 0; right < s.length(); right++)
        {
            cnt_s[s[right] - 'a']++; // 右端点字母进入窗口
            int left = right - p.length() + 1;
            if (left < 0)
            { // 窗口长度不足 p.length()
                continue;
            }
            if (cnt_s == cnt_p)
            {                        // s' 和 p 的每种字母的出现次数都相同
                ans.push_back(left); // s' 左端点下标加入答案
            }
            cnt_s[s[left] - 'a']--; // 左端点字母离开窗口
        }
        return ans;
    }
};

/**
 * 类似这种问题，要利用到char只有小写字母，所以只有26个，相比unordered_map，直接使用array<int,26>会更快一些，space也更少。
 */