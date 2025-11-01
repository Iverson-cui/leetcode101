#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end())
            return 0;

        unordered_set<string> beginSet{beginWord};
        unordered_set<string> endSet{endWord};
        unordered_set<string> visited;
        int steps = 1;

        while (!beginSet.empty() && !endSet.empty())
        {
            if (beginSet.size() > endSet.size())
                swap(beginSet, endSet);

            unordered_set<string> nextSet;

            for (const string &word : beginSet)
            {
                string current = word;
                for (int i = 0; i < current.size(); ++i)
                {
                    char original = current[i];
                    for (char c = 'a'; c <= 'z'; ++c)
                    {
                        if (c == original)
                            continue;
                        current[i] = c;

                        if (endSet.count(current))
                            return steps + 1;

                        if (wordSet.count(current) && !visited.count(current))
                        {
                            visited.insert(current);
                            nextSet.insert(current);
                        }
                    }
                    current[i] = original;
                }
            }

            beginSet = nextSet;
            steps++;
        }

        return 0;
    }
};

/**
 * 127是word ladder I，只需要返回最短路径的长度
 * 126是word ladder II，需要返回所有最短路径
 * 在127里用到了双向BFS，在起始点和目标点都给定，而且查找规则可正可逆的情况下，可以尝试。因为BFS每次搜索有可能会添加很多元素到queue里，所以可以先判断起始点的和目标点的哪个元素更少。直到接触即可。
 *
 * 虽然本题也是用BFS来做，但是并没有使用到queue，也不用太拘泥。用2个set，在最后进行替换，也可以实现queue的功能。
 */