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
    int numFriendRequests(vector<int> &ages)
    {
        int len = ages.size();
        sort(ages.begin(), ages.end());
        int result = 0;
        vector<int> freq(120, 0);
        for (int a : ages)
        {
            freq[a - 1]++;
        }
        printf("freq: ");
        for (int i = 0; i < 120; ++i)
        {
            if (freq[i] > 0)
                printf("ages: %d, %d ", i + 1, freq[i]);
        }
        printf("\n");
        for (int i = 0; i < len; ++i)
        {
            printf("ages[%d]=%d: ", i, ages[i]);
            int left = 0.5 * ages[i] + 7;
            int right = ages[i];
            for (int j = left + 2; j <= right; ++j)
            {
                if ((j >= 100) && (ages[i] < 99))
                {
                    continue;
                }
                result += freq[j - 1];
                if (j == ages[i])
                {
                    result--;
                }
                if (freq[j - 1] > 0)
                    printf("  add freq[%d]=%d\n", j - 1, freq[j - 1]);
            }
        }
        return result;
    }
};

int main(void)
{
    vector<int> ages = {16, 17, 18};
    Solution sol;
    cout << sol.numFriendRequests(ages) << endl;
    return 0;
}