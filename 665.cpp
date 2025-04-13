#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

bool checkPossibility(vector<int> &nums)
{
    int len = nums.size();
    if (len < 3)
    {
        return true;
    }
    else
    {
        int count = 0;
        for (int i = 0; i < len - 1; i++)
        {
            if (nums[i] > nums[i + 1])
            {
                // modifications must be made.
                count++;
                if (count > 1)
                {
                    return false;
                }
                if (i > 0 && (nums[i - 1] > nums[i + 1]) && (i < len - 2 && nums[i] > nums[i + 2]))
                {
                    return false;
                }
            }
        }
        return true;
    }
}