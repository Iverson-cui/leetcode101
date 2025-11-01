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
    int height_with_root(vector<vector<int>> &edges, int root, vector<vector<int>> &visited)
    {
        queue<int> q;
        for (auto &edge : edges)
        {
            if (find(visited.begin(), visited.end(), edge) == visited.end() && (edge[0] == root || edge[1] == root))
            {
                q.push(edge[0] == root ? edge[1] : edge[0]);
                visited.push_back(edge);
                // edges.erase(remove(edges.begin(), edges.end(), edge), edges.end());
            }
        }
        int height = 0;
        while (!q.empty())
        {
            int temp_height = height_with_root(edges, q.front());
            height = max(height, temp_height);
            q.pop();
        }
        edges.insert(edges.end(), visited.begin(), visited.end());
        return height + 1;
    }
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        vector<int> result;
        unordered_map<int, int> root_height_pair;
        int min_height = n;

        for (int i = 0; i < n; ++i)
        {
            vector<vector<int>> visited;
            root_height_pair[i] = height_with_root(edges, i, visited);
            if (root_height_pair[i] < min_height)
            {
                min_height = root_height_pair[i];
            }
        }
        for (const auto &pair : root_height_pair)
        {
            if (pair.second == min_height)
            {
                result.push_back(pair.first);
            }
        }
        return result;
    }
};

int main()
{
    vector<vector<int>> edges = {{1, 0}, {1, 2}, {1, 3}};
    Solution sol;
    vector<int> result = sol.findMinHeightTrees(4, edges);
    for (int root : result)
    {
        cout << root << " ";
    }
    cout << endl;
}