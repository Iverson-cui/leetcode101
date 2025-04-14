#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

// string minWindow(string s, string t)
// {
//     vector<int> times_t(128, 0);
//     // 统计t中ff每个字符出现的次数
//     for (int i = 0; i < t.size(); i++)
//     {
//         times_t[t[i]]++;
//     }
//     // 统计s中每个字符出现的次数
//     vector<int> times_s(128, 0);
//     for (int i = 0; i < s.size(); i++)
//     {
//         times_s[s[i]]++;
//     }
//     // l points to the beginning, r points to the end
//     int l = 0;
//     int r = s.size() - 1;
//     // before iteration, check if there exist a solution
//     for (int i = 0; i < 128; i++)
//     {
//         if (times_s[i] < times_t[i])
//         {
//             return "";
//         }
//     }
//     // this while is for getting the smallest right side
//     while (r > l)
//     {
//         // label for move
//         bool right = true;
//         // right pointer move to left one bit
//         times_s[s[r]]--;
//         r--;
//         for (int i = 0; i < 128; i++)
//         {
//             if (times_s[i] < times_t[i])
//             {
//                 // right pointer can not be removed any more.
//                 right = false;
//                 break;
//             }
//         }
//         if (~right)
//         {
//             r++;
//             break;
//         }
//     }
//     while (l < r)
//     {
//         // label for move
//         bool left = true;
//         // right pointer move to left one bit
//         times_s[s[l]]--;
//         l++;
//         for (int i = 0; i < 128; i++)
//         {
//             if (times_s[i] < times_t[i])
//             {
//                 // left pointer can not be removed any more.
//                 left = false;
//                 break;
//             }
//         }
//         if (~left)
//         {
//             l--;
//             break;
//         }
//     }
//     return s.substr(l, r - l + 1);
// }
string minWindow(string s, string t)
{
    vector<bool> valid(128, false);
    vector<int> freq(128, 0);
    // 统计t中的字符情况。valid记录对应字符有没有，freq记录有几个.也可以理解freq为t中对应字符还剩几个没满足，我们还需要几个
    for (int i = 0; i < t.length(); ++i)
    {
        valid[t[i]] = true;
        ++freq[t[i]];
    }
    // 移动滑动窗口，不断更改统计数据。
    // count记录了当前窗口中满足t中字符的个数。
    // 当count == t.length()时，说明当前窗口中包含了t中的所有字符。
    int count = 0;
    // min_l和min_length记录了当前最小的满足条件的窗口。遍历是从头到尾，这样才能找到最短的。
    int min_l = -1, min_length = -1;
    // 固定左边为0，先一步步移动右边。
    // 在找到一个可行的substr之后，这个循环继续进行，一直到r到达了s的末尾。
    for (int l = 0, r = 0; r < s.length(); ++r)
    {
        // s中的r位置的字符在t中没有出现过
        // 这个时候移动对于freq没有影响，所以直接跳过
        if (!valid[s[r]])
        {
            continue;
        }
        // 把r位置的字符加入频率统计，并检查是否补充了t中缺失的字符。
        // 先运行freq[s[r]]--，再将-之后的值和0比较。freq[s[r]]-- >= 0说明t中这个字符还缺少。count++是因为我们满足了一个字符。
        // freq可能会变成负数，意思是记录当前窗口中这个字符的数量已经超过了t中这个字符的数量。当超过的时候，不能算作又满足了t中的字符，所以对于count不进行更新。
        if (--freq[s[r]] >= 0)
        {
            ++count;
        }
        // 当count == t.length()时，说明当前窗口中包含了t中的所有字符。只有在这个时候 while循环才会被执行。
        // 本来是固定l右移r，现在固定r，尝试右移l，在不影响结果的情况下寻找最短串。
        while (count == t.length())
        {
            // 如果这个时候min_length还没改变，或者当前的窗口比之前记录的要小，就赋现在的值。
            if (min_length == -1 || r - l + 1 < min_length)
            {
                min_l = l;
                min_length = r - l + 1;
            }
            // 把l位置的字符移除频率统计，并检查t中对应字符是否重新缺失。
            // 如果t中有l对应的字符，并且移除这个字符后freq大于0，就说明移除是不对的，移除后就无法满足条件了。
            if (valid[s[l]] && ++freq[s[l]] > 0)
            {
                --count;
            }
            ++l;
        }
    }
    return min_length == -1 ? "" : s.substr(min_l, min_length);
}

/*
寻找的是最短的字符串，而不是最早出现的字符串。在注释的写法中，出现的问题是求的是最早出现的字符串。如果最短需要从头遍历到尾，记录下最短的开始和长度，每次有一个都要进行比较更新是否是最短的。
用一个count来记录满足的t的个数。否则就需要一个循环，对于所有valid的字符逐层进行判断。
2个指针的配合：先固定l不动，让r一直右移动，找到满足的r，这个时候右移动l，直到不满足条件。这个时候就可以更新min_l和min_length了。然后继续右移动r，直到r到达s的末尾。
*/