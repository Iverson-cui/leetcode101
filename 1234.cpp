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
    int arrayIndex(char c)
    {
        switch (c)
        {
        case 'Q':
            return 0;
        case 'W':
            return 1;
        case 'E':
            return 2;
        case 'R':
            return 3;
        default:
            return -1; // Should not reach here
        }
    }
    int balancedString(string s)
    {
        int len = s.length();
        int count[4] = {0}; // Index 0:'Q', 1:'W', 2:'E', 3:'R'
        for (char c : s)
        {
            count[arrayIndex(c)]++;
        }
        int required = len / 4;
        int left = 0, right = 1;
        int result = len;
        for (; right <= len; ++right)
        {
            printf("left: %d, right: %d\n", left, right);
            count[arrayIndex(s[right - 1])]--;
            printf("counts: Q=%d, W=%d, E=%d, R=%d\n", count[0], count[1], count[2], count[3]);
            // condition not holds, move left pointer
            while (count[0] <= required && count[1] <= required && count[2] <= required && count[3] <= required)
            {
                printf("Current valid window length: %d, results=%d\n", right - left, result);
                result = min(result, right - left);
                printf("Condition holds!\n");
                if (left < right)
                {
                    ++left;
                    count[arrayIndex(s[left - 1])]++;
                    printf("After moving left, counts: Q=%d, W=%d, E=%d, R=%d\n", count[0], count[1], count[2], count[3]);
                }
                else
                {
                    return 0;
                }
            }
        }
        return result;
    }
};

int main(void)
{
    Solution sol;
    string s = "WQWRQQQW";
    cout << sol.balancedString(s) << endl;
}

/**
 * 之前做的题都是越短越合法，找最长，思路是：left不变，right移动。移动之前一直符合，移动right直到不符合了，这个时候移动left，接着继续符合，再移动right，如此反复。
 * 这种题是越长越合法，找最短，反过来，即left不变，先移动right。right移动的一开始是不符合条件的，需要移动直到符合了。这个时候没必要再移动right，因为越长越合法，再移动right肯定合法，而且肯定不是最短。所以这个时候移动left收缩，收缩到不合法为止，再次移动right直到合法。
 */