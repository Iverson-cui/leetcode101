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
    bool queryString(string s, int n)
    {
        if (n == 1)
            // s.find will return npos if '1' is not found
            return s.find('1') != string::npos;

        int m = s.length();
        // calculate the MSB position of n
        // clz means count leading zeros
        int k = 31 - __builtin_clz(n); // n 的二进制长度减一
        // m is not long enough to contain all binary numbers of length k and k+1
        if (m < max(n - (1 << k) + k + 1, (1 << (k - 1)) + k - 1))
            return false;

        // 对于长为 k 的在 [lower, upper] 内的二进制数，判断这些数 s 是否都有
        auto check = [&](int k, int lower, int upper) -> bool
        {
            if (lower > upper)
                return true;
            unordered_set<int> seen;
            int mask = (1 << (k - 1)) - 1;
            // converts the first k-1 bits to integer
            int x = stoi(s.substr(0, k - 1), nullptr, 2);
            for (int i = k - 1; i < m; i++)
            {
                // & mask 可以去掉最高比特位，从而实现滑窗的「出」
                // << 1 | (s[i] - '0') 即为滑窗的「入」
                x = ((x & mask) << 1) | (s[i] - '0');
                if (lower <= x && x <= upper)
                    seen.insert(x);
            }
            return seen.size() == upper - lower + 1;
        };

        return check(k, n / 2 + 1, (1 << k) - 1) && check(k + 1, 1 << k, n);
    }
};

/**
 * 最简单的方法就是只对最高的k进行检查。如果k-bits的所有数都能表示，则k-1以下的肯定也能表示，这就将问题转化为滑动窗口。
 * 滑动窗口的问题，特别是定滑动，可以借助题目进行转化。本题本来需要检验从1到k bits的情况，通过脑筋急转弯转化到只需要检验k bits，进而将动滑窗转化为定滑窗。
 * 语法点上，注意lambda function，__builtin_clz的使用。
 */