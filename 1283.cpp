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
    bool helper(vector<int> &nums, int divisor, int threshold)
    {
        int sum = 0;
        for (int num : nums)
        {
            sum += (num + divisor - 1) / divisor;
        }
        return sum <= threshold;
    }
    int smallestDivisor(vector<int> &nums, int threshold)
    {
        int maxNum = *ranges::max_element(nums);
        int left = 1, right = maxNum;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (helper(nums, mid, threshold))
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main(void)
{
    Solution sol;
    vector<int> nums = {1, 2, 5, 9};
    int threshold = 6;
    int result = sol.smallestDivisor(nums, threshold);
    cout << "Smallest Divisor: " << result << endl;
    return 0;
}