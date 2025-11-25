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
    void printLeftRightArrays(const vector<int> &leftArray, const vector<int> &rightArray)
    {
        cout << "Left Array: ";
        for (int val : leftArray)
        {
            cout << val << " ";
        }
        cout << endl;
        cout << "Right Array: ";
        for (int val : rightArray)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    int takeCharacters(string s, int k)
    {
        int len = s.size();
        vector<int> totalCountLeft(3, 0);
        vector<int> totalCountRight(3, 0);
        int left = 0;
        int right = 0;
        for (int i = len - 1; i >= 0; --i)
        {
            totalCountLeft[s[i] - 'a']++;
            if (totalCountLeft[0] >= k && totalCountLeft[1] >= k && totalCountLeft[2] >= k)
            {
                left = i;
                break;
            }
        }
        if (left == 0 && (totalCountLeft[0] < k || totalCountLeft[1] < k || totalCountLeft[2] < k))
        {
            return -1;
        }
        // printf("initial left: %d, right: %d\n", left, right);
        // printLeftRightArrays(totalCountLeft, totalCountRight);
        int minSteps = len - left;
        while (left < len)
        {
            ++left;
            --totalCountLeft[s[left - 1] - 'a'];
            // printf("after move left, left: %d, right: %d\n", left, right);
            // printLeftRightArrays(totalCountLeft, totalCountRight);
            while ((totalCountLeft[0] + totalCountRight[0] < k) || (totalCountLeft[1] + totalCountRight[1] < k) || (totalCountLeft[2] + totalCountRight[2] < k))
            {
                // printf("!!!!!!!!!!!!!\n");
                ++totalCountRight[s[right] - 'a'];
                ++right;
            }
            // printf("after move right, left: %d, right: %d\n", left, right);
            // printLeftRightArrays(totalCountLeft, totalCountRight);
            // if (right + left >= len)
            // {
            //     break;
            // }
            minSteps = min(minSteps, right + (len - left));
            // printf("current minSteps: %d\n", minSteps);
        }
        return minSteps;
    }
};

int main(void)
{
    Solution solution;
    string s = "aabaaaacaabc";
    int k = 2;
    int result = solution.takeCharacters(s, k);
    cout << result << endl;
    return 0;
}