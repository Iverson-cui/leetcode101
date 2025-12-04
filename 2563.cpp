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
    long long countFairPairs(vector<int> &nums, int lower, int upper)
    {
        ranges::sort(nums);
        long long result = 0;
        int n = nums.size();
        int largest = nums[n - 1];
        int smallest = nums[0];
        for (int i = 0; i < n; i++)
        {
            if ((nums[i] + smallest > upper) || (nums[i] + largest < lower))
            {
                continue;
            }
            int low = lower - nums[i];
            int low_index = ranges::lower_bound(nums, low) - nums.begin();
            int up = upper - nums[i];
            int up_index = ranges::lower_bound(nums, up + 1) - nums.begin();
            if ((low_index != n) && (up_index != 0) && (up_index >= low_index))
            {
                result += (up_index - low_index);
            }
            if ((nums[i] >= low) && (nums[i] <= up))
            {
                result--;
            }
        }
        return result / 2;
    }
};

int main(void)
{
    Solution sol;
    vector<int> nums = {1, 7, 9, 2, 5};
    int lower = 11, upper = 11;
    long long result = sol.countFairPairs(nums, lower, upper);
    cout << result << endl;
    return 0;
}