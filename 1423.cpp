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
    int maxScore(vector<int> &cardPoints, int k)
    {
        vector<int> new_vec;
        int len = cardPoints.size();
        if (k >= len)
            return accumulate(cardPoints.begin(), cardPoints.end(), 0);
        new_vec.insert(new_vec.end(), cardPoints.end() - k, cardPoints.end());
        new_vec.insert(new_vec.end(), cardPoints.begin(), cardPoints.begin() + k);
        int max_score = 0;
        int current_score = 0;
        for (int i = 0; i < k + 1; i++)
        {
            if (i == 0)
            {
                current_score = accumulate(new_vec.begin(), new_vec.begin() + k, 0);
            }
            else
            {
                current_score = current_score - new_vec[i - 1] + new_vec[k + i - 1];
            }
            max_score = max(max_score, current_score);
        }
        return max_score;
    }
};

int maxScore(vector<int> &cardPoints, int k)
{
    int ans = 0;
    int n = cardPoints.size();
    int sum = 0;
    for (int i = n - k; i < n; i++)
    {
        sum += cardPoints[i];
    }

    ans = sum;

    for (int i = n; i < n + k; i++)
    {
        sum = sum - cardPoints[i - k] + cardPoints[i % n];
        ans = max(ans, sum);
    }

    return ans;
}

/**
 * 下面的解法更加方便，用modular arithmetic来处理环形数组的问题，而不是新建一个数组。其实思路是一样的，只是在空间复杂度上有巨大的优化。
 */