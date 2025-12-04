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
    vector<int> solveQueries(vector<int> &nums, vector<int> &queries)
    {
        int len = nums.size();
        unordered_map<int, vector<int>> occurIndex;
        for (int i = 0; i < len; i++)
        {
            occurIndex[nums[i]].push_back(i);
        }
        vector<int> result;
        for (int i = 0; i < queries.size(); i++)
        {
            int currentNum = nums[queries[i]];
            ranges::sort(occurIndex[currentNum]);
            printf("occurIndex[%d]: ", currentNum);
            for (auto val : occurIndex[currentNum])
            {
                printf("%d ", val);
            }
            printf("\n");
            if (occurIndex[currentNum].size() <= 1)
            {
                result.push_back(-1);
                continue;
            }

            // auto smaller = ranges::lower_bound(occurIndex[currentNum], queries[i]);
            int before = 0, after = 0;
            occurIndex[currentNum].insert(occurIndex[currentNum].begin(), occurIndex[currentNum].back() - nums.size());
            occurIndex[currentNum].push_back(occurIndex[currentNum][1] + nums.size());
            auto index = ranges::lower_bound(occurIndex[currentNum], queries[i]) - occurIndex[currentNum].begin();
            before = occurIndex[currentNum][index] - occurIndex[currentNum][index - 1];
            after = occurIndex[currentNum][index + 1] - occurIndex[currentNum][index];
            // if (index == 0)
            // {
            //     printf("index == 0\n");
            //     // occurIndex[currentNum].insert(occurIndex[currentNum].begin(), occurIndex[currentNum].back() - nums.size());
            //     printf("occurIndex[%d]: ", currentNum);
            //     for (auto val : occurIndex[currentNum])
            //     {
            //         printf("%d ", val);
            //     }
            //     printf("\n");
            //     before = occurIndex[currentNum][1] - occurIndex[currentNum][0];
            //     after = occurIndex[currentNum][2] - occurIndex[currentNum][1];
            // }
            // else if (index == occurIndex[currentNum].size() - 1)
            // {
            //     printf("index == size - 1\n");
            //     occurIndex[currentNum].push_back(occurIndex[currentNum][0] + nums.size());
            //     before = occurIndex[currentNum][index] - occurIndex[currentNum][index - 1];
            //     after = occurIndex[currentNum][index + 1] - occurIndex[currentNum][index];
            // }
            // else
            // {
            //     before = occurIndex[currentNum][index] - occurIndex[currentNum][index - 1];
            //     after = occurIndex[currentNum][index + 1] - occurIndex[currentNum][index];
            // }
            printf("before: %d, after: %d\n", before, after);
            int smallest = min(before, after);
            result.push_back(smallest);
        }
        return result;
    }
};

int main(void)
{
    Solution sol;
    vector<int> nums = {2, 10, 20, 20, 20};
    vector<int> queries = {1, 4, 2};
    vector<int> result = sol.solveQueries(nums, queries);
    for (auto val : result)
    {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}

/**
 * 上面的逻辑能做。思路是：要寻找距离某个元素最近的相同元素的最近距离，就用一个vector列出所有相同元素的下标，按照顺序排列后，找到该元素的下标，其前后就是离的最近的。但是超出时间限制。
 * 下面的逻辑和上面相同，上面有一些bug没有处理好，下面的代码进行了修正。
 */

class Solution
{
public:
    vector<int> solveQueries(vector<int> &nums, vector<int> &queries)
    {
        unordered_map<int, vector<int>> indices;
        for (int i = 0; i < nums.size(); i++)
        {
            indices[nums[i]].push_back(i);
        }

        int n = nums.size();
        for (auto &[_, p] : indices)
        {
            // 前后各加一个哨兵
            int i0 = p[0];
            p.insert(p.begin(), p.back() - n);
            p.push_back(i0 + n);
        }

        for (int &i : queries)
        { // 注意这里是引用
            auto &p = indices[nums[i]];
            if (p.size() == 3)
            {
                i = -1;
            }
            else
            {
                int j = ranges::lower_bound(p, i) - p.begin();
                i = min(i - p[j - 1], p[j + 1] - i);
            }
        }
        return queries;
    }
};