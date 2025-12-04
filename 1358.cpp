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
    int numberOfSubstrings(string s)
    {
        int len = s.size();
        int left = 0, right = 0;
        int count[3] = {0};
        int result = 0;
        for (; right < len; ++right)
        {
            count[s[right] - 'a']++;
            while (count[0] > 0 && count[1] > 0 && count[2] > 0)
            {
                count[s[left] - 'a']--;
                ++left;
                result += len - right;
            }
        }
        return result;
    }
};

/**
 * 这类问题属于越长越合法，整体代码框架相同，外层for，内层while，根据条件收缩指针。只不过因为越长越合法，对于一个符合条件的left和right，我们统计left不变right一直到末尾的情况，result+=len-right。其余和类似题目相同。
 */