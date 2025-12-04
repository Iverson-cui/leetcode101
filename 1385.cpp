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
    int findTheDistanceValue(vector<int> &arr1, vector<int> &arr2, int d)
    {
        ranges::sort(arr2);
        // printf("sorted arr2: ");
        // for (auto num : arr2)
        // {
        //     printf("%d ", num);
        // }
        // printf("\n");
        int result = 0;
        for (auto num : arr1)
        {
            // printf("num=%d, num+d+1=%d, num-d=%d\n", num, num + d + 1, num - d);
            int bigger = ranges::lower_bound(arr2, num + d + 1) - arr2.begin();
            // printf("bigger=%d\n", bigger);
            int smaller = ranges::lower_bound(arr2, num - d) - arr2.begin();
            // printf("smaller=%d\n", smaller);
            if (bigger == smaller)
            {
                result++;
            }
        }
        return result;
    }
};

int main()
{
    vector<int> arr1 = {4, 5, 8};
    vector<int> arr2 = {10, 9, 1, 8};
    int d = 2;
    Solution sol;
    int res = sol.findTheDistanceValue(arr1, arr2, d);
    cout << res << endl;
    return 0;
}