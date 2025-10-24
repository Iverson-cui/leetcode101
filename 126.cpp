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
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        unordered_map<string, int> depthMap;
        vector<vector<string>> ans;

        // BFS to find the shortest path
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        queue<string> q;
        q.push(beginWord);
        depthMap[beginWord] = 1;
        wordSet.erase(beginWord);

        while (!q.empty())
        {
            string word = q.front();
            q.pop();
            int steps = depthMap[word];
            // found shortest path, stop BFS
            if (word == endWord)
                break;
            // try each position of the word
            for (int i = 0; i < word.size(); ++i)
            {
                char original = word[i];
                for (char ch = 'a'; ch <= 'z'; ++ch)
                {
                    // modify the i-th character
                    word[i] = ch;
                    // if modified word is in the set
                    if (wordSet.count(word))
                    {
                        // add to queue
                        q.push(word);
                        // mark as visited
                        wordSet.erase(word);
                        // record depth
                        depthMap[word] = steps + 1;
                    }
                }
                word[i] = original;
            }
        }

        // DFS to find all paths
        // if endWord is reached
        if (depthMap.count(endWord))
        {
            vector<string> seq = {endWord};
            dfs(endWord, beginWord, seq, depthMap, ans);
        }

        // endWord not reached, no path, return empty list
        return ans;
    }

private:
    void dfs(string word, string beginWord, vector<string> &seq, unordered_map<string, int> &depthMap, vector<vector<string>> &ans)
    {
        if (word == beginWord)
        {
            reverse(seq.begin(), seq.end());
            ans.push_back(seq);
            reverse(seq.begin(), seq.end());
            return;
        }

        int steps = depthMap[word];
        for (int i = 0; i < word.size(); ++i)
        {
            char original = word[i];
            for (char ch = 'a'; ch <= 'z'; ++ch)
            {
                word[i] = ch;
                if (depthMap.count(word) && depthMap[word] + 1 == steps)
                {
                    seq.push_back(word);
                    dfs(word, beginWord, seq, depthMap, ans);
                    seq.pop_back();
                }
            }
            word[i] = original;
        }
    }
};