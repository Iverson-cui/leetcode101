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
    int val(char c)
    {
        return c - 'a' + 1;
    }
    int hash(string partialString, int power, int modulo)
    {
        int len = partialString.size();
        long long result = 0;
        cout << "power=" << power << endl;
        cout << "modulo=" << modulo << endl;
        for (int i = len - 1; i >= 0; --i)
        {
            // cout << "  Processing char '" << partialString[i] << "' (val=" << val(partialString[i]) << ")" << endl;
            // cout << "  Before: result=" << result << endl;
            result = (result * power % modulo + val(partialString[i]));
            // cout << "  After: result=" << result << endl;
        }
        // cout << "Hash of " << partialString << " is " << result << endl;
        return result % modulo;
    }
    string subStrHash(string s, int power, int modulo, int k, int hashValue)
    {
        // if ((power == 0) && (hashValue == 0))
        // {
        //     return s.substr(0, k);
        // }
        string temp;
        int len = s.size();
        // cout << "val of substring is " << val(s[0]) << endl;
        int currHash = hash(s.substr(len - k, k), power, modulo);
        if (currHash == hashValue)
        {
            return s.substr(len - k, k);
        }
        for (int i = len - k - 1; i >= 0; --i)
        {

            currHash = ((currHash - val(s[i + k]) * (int)pow(power, k - 1)) * power + val(s[i])) % modulo;
            // cout << "Hash of " << s.substr(i, k) << " is " << currHash << endl;
            while (currHash < 0)
            {
                currHash += modulo;
            }
            if (currHash == hashValue)
            {
                temp = s.substr(i, k);
            }
        }
        return temp.empty() ? "Damn, no answer!" : temp;
    }
};

int main(void)
{
    Solution sol;
    string s = "fbxzaad";
    int power = 31;
    int modulo = 100;
    int k = 3;
    int hashValue = 32;
    string result = sol.subStrHash(s, power, modulo, k, hashValue);
    cout << "Result: " << result << endl;
    return 0;
}