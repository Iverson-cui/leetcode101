#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int lexicography(string &a, string &b)
{
    int len = a.size();
    for (int i = 0; i < len; i++)
    {
        if (a[i] < b[i])
        {
            return 0;
        }
        else if (a[i] > b[i])
        {
            return 1;
        }
    }
    return 0; // return a if both strings are equal
}

string findLongestWord(string s, vector<string> &dictionary)
{
    int s_ptr;
    int dic_ptr;
    int len = 0;
    int pos = 0;
    for (int i = 0; i < dictionary.size(); i++)
    {
        s_ptr = 0;
        dic_ptr = 0;
        for (; s_ptr < s.size();)
        {
            // if the char is same
            if (s[s_ptr] == dictionary[i][dic_ptr])
            {
                s_ptr++;
                dic_ptr++;
            }
            // if the char is not the same
            else
            {
                ++s_ptr;
            }
            // dic_ptr has moved to the end, this is a valid word
            if (dic_ptr == dictionary[i].size())
            {
                // check if the current word is longer than the previous longest word
                if (len < dic_ptr)
                {
                    len = dic_ptr;
                    pos = i;
                    break;
                }
                if (len == dic_ptr)
                {
                    // check if the current word is lexicographically smaller
                    if (lexicography(dictionary[i], dictionary[pos]) == 0)
                    {
                        pos = i;
                    }
                    break;
                }
                // s_ptr has moved to the end, this is not a valid word
                if (s_ptr == s.size())
                {
                    break;
                }
            }
        }
    }
    if ((len == 0) && (pos == 0))
    {
        return ""; // return empty string if no valid word found
    }
    return dictionary[pos]; // return the longest valid word found
}
int main(void)
{
    string s = "abpcplea";
    vector<string> dictionary = {"ale", "apple", "monkey", "plea"};
    cout << findLongestWord(s, dictionary) << endl;
    cout << "hello world" << endl;
    return 0;
}