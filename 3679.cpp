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
    int minArrivalsToDiscard(vector<int> &arrivals, int w, int m)
    {
        int len = arrivals.size();
        unordered_map<int, int> freq_map;
        freq_map[0] = len;
        int discard_count = 0;
        for (int i = 0; i < len; i++)
        {
            if (i < w)
            {
                freq_map[arrivals[i]]++;
                if (freq_map[arrivals[i]] > m)
                {
                    freq_map[arrivals[i]]--;
                    arrivals[i] = 0;
                    discard_count++;
                }
            }
            else
            {
                freq_map[arrivals[i - w]]--;
                freq_map[arrivals[i]]++;
                if (freq_map[arrivals[i]] > m)
                {
                    freq_map[arrivals[i]]--;
                    arrivals[i] = 0;
                    discard_count++;
                }
            }
        }
        return discard_count;
    }
};

/**
 * 这是滑动窗口问题中很常见的“软删除”思路：通常遇到丢弃需求会先想到物理删除元素，但本题的关键坑点在于“必须维持固定窗口滑动”——物理删除会破坏数组索引连续性，导致窗口边界无法准确定位。因此改用“虚拟标记”实现软删除：被丢弃的元素仅标记为特定值（如0），后续统计频率或处理窗口滑动时，只要碰到该标记就判定为无效元素，不纳入频率计算，既保证了窗口滑动的正确性，又简化了逻辑。
 * 这里需要注意，题目隐含贪心的想法：对于第i天进来的货物，即使这个货物并未超过m个，也可以选择丢弃。换个角度，比如这一天到来的货物超过了m个，则可以选择在之前收到这个货物的时候提前丢弃。到底选择哪个是最优解？对于当前的window来看的话，没有区别，但是对于以后即将到来的同样货物来看，如果提前容纳进来，会使得其更早的退出window，后续遇到了就不用再丢了。所以我们在允许的情况下先包含进来，满了再丢。
 */