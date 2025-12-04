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
    int findSpecialInteger(vector<int> &arr)
    {
        int len = arr.size();
        int threshold = 0;
        if (len % 4 == 0)
        {
            threshold = len / 4;
        }
        else
        {
            threshold = (len + 4 - 1) / 4;
        }
        // int count1 = 0;
        // int count2 = ranges::lower_bound(arr, arr[0] + 1) - arr.begin();
        int currentIndex = 0;
        int nextIndex = ranges ::lower_bound(arr, arr[0] + 1) - arr.begin();
        while (nextIndex - currentIndex <= threshold)
        {
            if (nextIndex == len)
            {
                break;
            }
            currentIndex = nextIndex;
            nextIndex = ranges::lower_bound(arr, arr[currentIndex] + 1) - arr.begin();
        }
        if (nextIndex - currentIndex > threshold)
        {
            return arr[currentIndex];
        }
        else
        {
            return arr[len - 1];
        }
    }
};

/**
 * 上面的做法没有问题。但是借助题干可以做进一步优化。因为题中说了一定有唯一答案，所以一定有连续25%的数字是相同的，所以可以证明只需要查询3个点处，这3个点里必定有一个点包含25%的数字。查了前两个都不是，就可以直接返回最后一个点处的数字。这样整个题目只需要用4次二分就可以做。
 */