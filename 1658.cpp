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
    int minOperations(vector<int> &nums, int x)
    {
        int len = nums.size();
        int left = 0, right = 0;
        int Operations = 0;
        int minOps = len + 1;
        int sum = 0;
        while (sum < x)
        {
            if (right >= len)
            {
                return -1;
            }
            sum += nums[right++];
        }
        if (sum == x)
        {
            // printf("Initial sum equals x, right=%d\n", right);
            minOps = right - left;
            sum -= nums[right - 1];
            --right;
        }
        else
        {
            // printf("Initial sum exceeds x, right=%d\n", right);
            sum -= nums[right - 1];
            --right;
            // printf("Adjusting right to %d, sum=%d\n", right, sum);
        }
        while ((right >= left) && (right > -1))
        {
            // printf("Current left=%d, right=%d, sum=%d\n", left, right, sum);
            if (sum + nums[(left - 1 + len) % len] < x)
            {
                // printf("Sum + %d %% len] < x\n", nums[(left - 1 + len) % len]);
                --left;
                sum += nums[(left + len) % len];
                // printf("New left=%d, sum=%d\n", left, sum);
            }
            else if (sum + nums[(left - 1 + len) % len] == x)
            {
                // printf("Found sum + %d %% len] == x\n", nums[(left - 1 + len) % len]);
                --left;
                minOps = min(minOps, right - left);
                sum += nums[(left + len) % len];
                // printf("New left=%d, sum=%d, minOps=%d\n", left, sum, minOps);
            }
            else
            {
                // printf("Sum + %d %% len] > x\n", nums[(left - 1 + len) % len]);
                sum -= nums[(right - 1 + len) % len];
                --right;
                // printf("New right=%d, sum=%d\n", right, sum);
            }
        }
        return minOps == len + 1 ? -1 : minOps;
    }
};

int main(void)
{
    Solution sol;
    vector<int> nums = {3, 2, 20, 1, 1, 3};
    printf("Input array: ");
    for (int num : nums)
    {
        printf("%d ", num);
    }
    printf("\n");
    int x = 10;
    int res = sol.minOperations(nums, x);
    cout << res << endl;
    return 0;
}