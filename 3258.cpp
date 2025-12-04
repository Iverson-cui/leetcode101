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
    int countKConstraintSubstrings(string s, int k)
    {
        int len = s.size();
        int left = 0, right = 0;
        int boolCount[2] = {0, 0};
        int result = 0;
        for (; right < len; ++right)
        {
            boolCount[s[right] - '0']++;
            while (boolCount[0] > k && boolCount[1] > k)
            {
                boolCount[s[left] - '0']--;
                ++left;
            }
            result += right - left + 1;
        }
        return result;
    }
};
/**
 * 这类滑动窗口的模板就是：外层for循环找right和len的关系，内层先把s[right]计算进去，之后移动left直到满足条件。满足后，这就是right取固定值的时候left的最小值，计算子数组的个数即可。
 */