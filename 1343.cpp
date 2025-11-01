#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
public:
    int numOfSubarrays(vector<int> &arr, int k, int threshold)
    {
        int targetSum = threshold * k;
        int currSum = 0;
        int count = 0;
        int start = 0;
        int end = k - 1;
        int len = arr.size();
        for (int i = 0; i < k; i++)
        {
            currSum += arr[i];
        }
        while (true)
        {
            if (currSum >= targetSum)
            {
                ++count;
            }
            if (end + 1 >= len)
            {
                break;
            }
            currSum = currSum - arr[start] + arr[end + 1];
            ++start;
            ++end;
        }
        return count;
    }
};