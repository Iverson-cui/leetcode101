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
    int numKLenSubstrNoRepeats(string s, int k)
    {
        int n = s.size();
        if (k > n || k > 26)
        {
            return 0;
        }
        int cnt[128]{};
        int ans = 0;
        for (int i = 0, j = 0; i < n; ++i)
        {
            ++cnt[s[i]];
            while (cnt[s[i]] > 1 || i - j + 1 > k)
            {
                --cnt[s[j++]];
            }
            ans += i - j + 1 == k;
        }
        return ans;
    }
};

/**
 * 看上去是定滑窗问题，其实用动滑窗可以很快的解决。如果定，判断其中是否有重复字符需要在时间或空间上带来较大的overhead。采用上文，先动右边界，不断叠加。如果右边界这次循环的数出现过多次或窗口长度超过k，则动左边界收缩窗口，直到窗口合法为止。每次当窗口长度等于k时，说明找到一个合法子串，答案加一。
 */