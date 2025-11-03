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
    int minFlips(string s)
    {
        int n = s.size(), ans = n, cnt = 0;
        for (int i = 0; i < n * 2 - 1; i++)
        {
            cnt += (s[i % n] ^ i) & 1;
            int left = i - n + 1;
            if (left < 0)
            {
                continue;
            }
            ans = min({ans, cnt, n - cnt});
            cnt -= (s[left] ^ left) & 1;
        }
        return ans;
    }
};

/**
 * 使用滑窗的方法。既然操作1的次数不做任何限制，则列出一个长度为n的数组经过任意次操作1得到的结果得到的数组，长度为2n-1，每个长度为n的滑窗里的子字符串都是一种可能。
 * 对于一个n字符串，我们可以执行操作2 to 2个方向，1010...或0101...，所以要分别统计这两个方向的操作1的次数，并分别取最小值。统计的方法为：观察到1个位如果满足其值==其index%2，那就是0101方向，反之就是1010方向，所以只需要统计一个，另一个相减即可。
 */
