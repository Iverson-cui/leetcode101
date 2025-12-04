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
    int lowerbound(vector<char> &letters, char target)
    {
        int left = 0, right = letters.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (letters[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return left;
    }
    char nextGreatestLetter(vector<char> &letters, char target)
    {
        int index = lowerbound(letters, target + 1);
        if (index == letters.size())
        {
            return letters[0];
        }
        return letters[index];
    }
};