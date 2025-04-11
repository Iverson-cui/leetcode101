#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
// takes in two vectors of size 2, compare the second element of them and sort by ascending order
bool compareByDifference(const vector<int> &a,
                         const vector<int> &b)
{
    if (a[1] == b[1])
    {
        // When second elements are equal
        if (a[1] == 0)
        {
            // If second element is 0, sort in ascending order of first element
            return a[0] < b[0];
        }
        else
        {
            // If second element is not 0, sort in descending order of first element
            return a[0] > b[0];
        }
    }
    return a[1] < b[1]; // First sort by second element
}

vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
{

    int count = 0;
    sort(people.begin(), people.end(),
         compareByDifference);
    vector<vector<int>> result;
    while (count < people.size() && people[count][1] == 0)
    {
        result.push_back(people[count]);
        count++;
    }
    // Remove processed elements by shifting the vector
    if (count > 0)
    {
        people.erase(people.begin(), people.begin() + count);
    }
    // now the people vector has no element with second entry 0.
    // iteration of people vector
    int len = people.size();
    for (int i = 0; i < len; i++)
    {
        int temp = 0;
        // iteration of result vector
        for (int j = 0; j < result.size(); j++)
        {
            if (result[j][0] < people[i][0])
            {
                temp++;
            }
        }
        result.insert(result.begin() + temp + people[i][1], people[i]);
    }
    return result;
}