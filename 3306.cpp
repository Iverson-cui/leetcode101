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
    int indexHelper(char a)
    {
        if (a == 'a')
        {
            return 0;
        }
        else if (a == 'e')
        {
            return 1;
        }
        else if (a == 'i')
        {
            return 2;
        }
        else if (a == 'o')
        {
            return 3;
        }
        else if (a == 'u')
        {
            return 4;
        }
        else
        {
            return 5;
        }
    }
    long long solve(string &word, int k)
    {
        int len = word.size();
        long long result = 0;
        int left = 0, right = 0;
        int count = 0;
        int charCount[6] = {0};
        int satisfyVowalCount = 0;
        for (; right < len; ++right)
        {
            charCount[indexHelper(word[right])]++;
            if ((charCount[indexHelper(word[right])] == 1) && (indexHelper(word[right]) != 5))
            {
                satisfyVowalCount++;
            }
            while ((satisfyVowalCount == 5) && (charCount[5] >= k))
            {
                result += (len - right);
                charCount[indexHelper(word[left])]--;
                if ((charCount[indexHelper(word[left])] == 0) && (indexHelper(word[left]) != 5))
                {
                    satisfyVowalCount--;
                }
                left++;
            }
        }
        return result;
    }
    long long countOfSubstrings(string word, int k)
    {
        return solve(word, k) - solve(word, k + 1);
    }
};