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
    int characterReplacement(string s, int k)
    {
        int len = s.size();
        vector<vector<int>> pos_lists(26);
        for (int i = 0; i < len; ++i)
        {
            pos_lists[s[i] - 'A'].push_back(i);
        }
        printf("pos_lists:\n");
        for (int i = 0; i < 26; ++i)
        {
            printf("%c: ", 'A' + i);
            for (int pos : pos_lists[i])
            {
                printf("%d ", pos);
            }
            printf("\n");
        }
        int ans = 1;
        for (const auto &pos_list : pos_lists)
        {

            int left = 0, right = 1;
            int size = pos_list.size();
            if (size < 1)
            {
                continue;
            }
            if (size == 1)
            {
                ans = max(ans, 1 + k);
                if (ans >= len)
                {
                    return len;
                }
                continue;
            }
            printf("For pos list: ");
            for (int pos : pos_list)
            {
                printf("%d ", pos);
            }
            printf("\n");
            for (; (right < size) && (left < right); ++right)
            {
                printf("  right=%d, left=%d\n", right, left);
                if (pos_list[right] - pos_list[left] + 1 - (right - left + 1) > k)
                {
                    printf("    shrink window\n");
                    ++left;
                }
                else if (pos_list[right] - pos_list[left] + 1 - (right - left + 1) == k)
                {
                    printf("    exact fit\n");
                    ans = max(ans, pos_list[right] - pos_list[left] + 1);
                    printf("    ans=%d\n", ans);
                }
                else
                {
                    printf("    can still expand\n");
                    if (pos_list[right] - pos_list[left] + 1 + k - (pos_list[right] - pos_list[left] + 1 - (right - left + 1)) >= len)
                    {
                        return len;
                    }
                    ans = max(ans, pos_list[right] - pos_list[left] + 1 + k - (pos_list[right] - pos_list[left] + 1 - (right - left + 1)));
                    printf("    ans=%d\n", ans);
                }
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    string s = "ABCDE";
    int k = 1;
    int ans = sol.characterReplacement(s, k);
    cout << ans << endl;
    return 0;
}

/**
 * 按照2831的逻辑，可以实现，只是corner case较多。
 * 下面的解法更好理解一些。
 */

class Solution
{
public:
    int characterReplacement(string s, int k)
    {
        int n = s.size();
        int occurs[26]{0};
        for (auto &ch : s)
        {
            if (occurs[ch - 'A'] == 0)
                occurs[ch - 'A'] = 1;
        }
        int res = 0;
        for (int t = 0; t < 26; t++)
        {
            if (!occurs[t])
                continue;
            char tar = 'A' + t;
            int i = 0;
            int j = 0;
            int cnt = 0;
            while (j < n)
            {
                if (s[j] != tar)
                    cnt++;
                while (cnt > k)
                {
                    if (s[i] != tar)
                        cnt--;
                    i++;
                }
                res = max(res, j - i + 1);
                j++;
            }
        }
        return res;
    }
};