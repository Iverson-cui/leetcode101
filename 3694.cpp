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
    struct ArrayHasher
    {
        std::size_t operator()(const std::array<int, 4> &a) const
        {
            std::size_t h = 0;
            for (auto e : a)
            {
                // A simple way to combine hashes of elements
                h ^= std::hash<int>{}(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
            }
            return h;
        }
    };
    void move(const string &s, int start, int k, array<int, 4> &count)
    {
        // string window = s.substr(start, k);
        // printf("window:%s\n", window.c_str());
        // count = {0, 0, 0, 0};
        if (start == 0)
        {
            for (int i = start; i < start + k; i++)
            {
                if (s[i] == 'U')
                    count[0]++;
                else if (s[i] == 'D')
                    count[1]++;
                else if (s[i] == 'L')
                    count[2]++;
                else if (s[i] == 'R')
                    count[3]++;
                else
                    ;
            }
        }
        else
        {
            if (s[start - 1] == 'U')
                count[0]--;
            else if (s[start - 1] == 'D')
                count[1]--;
            else if (s[start - 1] == 'L')
                count[2]--;
            else if (s[start - 1] == 'R')
                count[3]--;
            else
                ;
            if (s[start + k - 1] == 'U')
                count[0]++;
            else if (s[start + k - 1] == 'D')
                count[1]++;
            else if (s[start + k - 1] == 'L')
                count[2]++;
            else if (s[start + k - 1] == 'R')
                count[3]++;
            else
                ;
        }
        // printf("before U:%d D:%d L:%d R:%d\n", count[0], count[1], count[2], count[3]);
        // printf("min UD:%d LR:%d\n", min(count[0], count[1]), min(count[2], count[3]));
        int min01 = min(count[0], count[1]);
        int min23 = min(count[2], count[3]);
        count[0] -= min01;
        count[1] -= min01;
        count[2] -= min23;
        count[3] -= min23;
        // printf("after min U:%d D:%d L:%d R:%d\n", count[0], count[1], count[2], count[3]);

        // printf("U:%d D:%d L:%d R:%d\n", count[0], count[1], count[2], count[3]);
        // return count;
    }
    int distinctPoints(string s, int k)
    {
        unordered_set<array<int, 4>, ArrayHasher> existed;
        int len = s.size();
        int diff = 0;
        array<int, 4> count = {0, 0, 0, 0};
        if (k == len)
        {
            return 1;
        }
        for (int i = 0; i <= len - k; ++i)
        {
            move(s, i, k, count);
            if (existed.count(count) == 0)
            {
                existed.insert(count);
                ++diff;
            }
        }
        return diff;
    }
};

int main(void)
{
    string s = "DURLU";
    int k = 2;
    printf("%d\n", Solution().distinctPoints(s, k));
}

/**
 * 为了优化时间和空间上的复杂度，采用渐进方法而不是每个window都从头计算。补充一个知识点，对于unordered_set，如果存储自定义类型，比如array，需要自己提供hash函数。
 */