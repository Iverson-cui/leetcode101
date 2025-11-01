#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

int minLength(string beginWord, string endWord, vector<string> &wordList, unordered_map<string, int> *word_steps)
{
    unordered_set<string> start_set({beginWord});
    unordered_set<string> end_set({endWord});
    unordered_set<string> word_set(wordList.begin(), wordList.end());
    // unordered_set<string> visited;
    // if beginWord not in word_steps, it will be auto-created here
    (*word_steps)[beginWord] = 1;
    // visited.insert(beginWord);
    word_set.erase(beginWord);

    int steps = 1;
    if (!word_set.count(endWord))
    {
        return 0;
    }
    while (1)
    {
        unordered_set<string> next_set;
        // search in min set
        // if (start_set.size() > end_set.size())
        // {
        //     swap(start_set, end_set);
        // }
        for (auto word : start_set)
        {
            int word_len = word.size();
            for (int i = 0; i < word_len; i++)
            {
                char original_char = word[i];
                for (char c = 'a'; c <= 'z'; c++)
                {
                    if (c == original_char)
                    {
                        continue;
                    }
                    word[i] = c;
                    if (end_set.count(word))
                    {
                        (*word_steps)[word] = steps + 1;
                        return steps + 1;
                    }
                    if (word_set.count(word))
                    {
                        next_set.insert(word);
                        word_set.erase(word);
                        (*word_steps)[word] = steps + 1;
                    }
                    word[i] = original_char;
                }
            }
        }
        if (next_set.empty())
        {
            return 0;
        }
        start_set.swap(next_set);
        ++steps;
    }
}

void backtrace(vector<vector<string>> &results, vector<string> &path, string startWord, unordered_map<string, int> &word_steps)
{
    printf("Current path: [");
    for (size_t i = 0; i < path.size(); ++i)
    {
        printf("\"%s\"", path[i].c_str());
        if (i < path.size() - 1)
            printf(", ");
    }
    printf("]\n");
    string currentWord = path.back();
    int target_distance = word_steps[currentWord] - 1;
    printf("Backtracing from %s, target distance: %d\n", currentWord.c_str(), target_distance);
    int word_len = currentWord.size();
    stack<string> temp_word_stack;
    printf("Exploring neighbors of %s:\n", currentWord.c_str());
    for (int i = 0; i < word_len; ++i)
    {
        char original_char = currentWord[i];
        for (char c = 'a'; c <= 'z'; ++c)
        {
            if (c == original_char)
            {
                continue;
            }
            currentWord[i] = c;
            printf("  Checking neighbor: %s\n", currentWord.c_str());
            if (word_steps.count(currentWord) && word_steps[currentWord] == target_distance)
            {
                if (currentWord == startWord)
                {
                    path.push_back(currentWord);
                    vector<string> valid_path = path;
                    reverse(valid_path.begin(), valid_path.end());
                    results.push_back(valid_path);
                    path.pop_back();
                }
                else
                {
                    temp_word_stack.push(currentWord);
                }
            }
        }
        currentWord[i] = original_char;
    }
    while (!temp_word_stack.empty())
    {
        string nextWord = temp_word_stack.top();
        temp_word_stack.pop();
        path.push_back(nextWord);
        printf("Now path is: [");
        for (size_t i = 0; i < path.size(); ++i)
        {
            printf("\"%s\"", path[i].c_str());
            if (i < path.size() - 1)
                printf(", ");
        }
        printf("]\n");
        backtrace(results, path, startWord, word_steps);
        path.pop_back();
        printf("Backtracked to path: [");
        for (size_t i = 0; i < path.size(); ++i)
        {
            printf("\"%s\"", path[i].c_str());
            if (i < path.size() - 1)
                printf(", ");
        }
        printf("]\n");
    }
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
{
    unordered_map<string, int> word_steps;
    int min_steps = minLength(beginWord, endWord, wordList, &word_steps);
    printf("%d\n", min_steps);
    vector<vector<string>> results;
    vector<string> path = {endWord};
    // Print word_steps for debugging
    cout << "Word steps map:\n";
    for (const auto &entry : word_steps)
    {
        cout << "  \"" << entry.first << "\": " << entry.second << "\n";
    }
    cout << "\n";
    backtrace(results, path, beginWord, word_steps);
    return results;
}

void printResult(const vector<vector<string>> &result)
{
    cout << "[\n";
    for (const auto &path : result)
    {
        cout << "  [";
        for (size_t i = 0; i < path.size(); ++i)
        {
            cout << "\"" << path[i] << "\"";
            if (i < path.size() - 1)
                cout << ", ";
        }
        cout << "]\n";
    }
    cout << "]\n";
}

int main()
{
    // Test Case 1: Standard case with multiple shortest paths
    cout << "Test Case 1: Multiple shortest paths\n";
    string beginWord1 = "hot";
    string endWord1 = "dog";
    vector<string> wordList1 = {"hot", "dot", "dog"};

    vector<vector<string>> result1 = findLadders(beginWord1, endWord1, wordList1);
    // cout << "Expected: 2 paths of length 5\n";
    cout << "Output:\n";
    printResult(result1);
    cout << "\n";

    // // Test Case 2: No valid transformation
    // cout << "Test Case 2: No valid path\n";
    // string beginWord2 = "hit";
    // string endWord2 = "cog";
    // vector<string> wordList2 = {"hot", "dot", "dog", "lot", "log"}; // Missing "cog"

    // vector<vector<string>> result2 = findLadders(beginWord2, endWord2, wordList2);
    // cout << "Expected: Empty result []\n";
    // cout << "Output:\n";
    // printResult(result2);
    // cout << "\n";

    // // Test Case 3: Single path
    // cout << "Test Case 3: Single shortest path\n";
    // string beginWord3 = "a";
    // string endWord3 = "c";
    // vector<string> wordList3 = {"a", "b", "c"};

    // vector<vector<string>> result3 = findLadders(beginWord3, endWord3, wordList3);
    // cout << "Expected: 1 path: [\"a\", \"c\"]\n";
    // cout << "Output:\n";
    // printResult(result3);
    // cout << "\n";

    // // Test Case 4: Longer chain
    // cout << "Test Case 4: Longer transformation chain\n";
    // string beginWord4 = "red";
    // string endWord4 = "tax";
    // vector<string> wordList4 = {"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};

    // vector<vector<string>> result4 = findLadders(beginWord4, endWord4, wordList4);
    // cout << "Expected: Multiple paths of length 4\n";
    // cout << "Output:\n";
    // printResult(result4);
    // cout << "\n";

    // // Test Case 5: beginWord equals endWord neighbor
    // cout << "Test Case 5: Direct transformation\n";
    // string beginWord5 = "hot";
    // string endWord5 = "dot";
    // vector<string> wordList5 = {"hot", "dot", "dog"};

    // vector<vector<string>> result5 = findLadders(beginWord5, endWord5, wordList5);
    // cout << "Expected: 1 path: [\"hot\", \"dot\"]\n";
    // cout << "Output:\n";
    // printResult(result5);

    return 0;
}

/**
 * 先用DFS来寻找最短路径的长度，同时记录每个单词到起始单词的最短距离。找到长度后，再用回溯法（backtracking）+深度优先搜索的方法，从结束单词开始，沿着记录的最短距离反向构建所有可能的最短路径，直到回到起始单词为止。
 */