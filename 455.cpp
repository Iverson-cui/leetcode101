#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

int max_full(vector<int> &kids, vector<int> &cookies)
{
    sort(kids.begin(), kids.end());
    sort(cookies.begin(), cookies.end());
    int full = 0;
    int len_cookies = cookies.size();
    int len_kids = kids.size();
    while (len_cookies > 0 && len_kids > 0)
    {
        if (cookies[len_cookies - 1] >= kids[len_kids - 1])
        {
            full++;
            len_cookies--;
            len_kids--;
        }
        else
        {
            len_kids--;
        }
        return full;
    }
}

int main()
{
    vector<int> kids = {1, 2, 3};
    vector<int> cookies = {1, 1};
    cout << max_full(kids, cookies) << endl;
    return 0;
}

/*
最终问题是最多有多少个孩子能满足，使用贪心算法，将视角缩小到最容易满足或最不容易满足的孩子，一个个解决。贪心的重点是要证明局部最优一步步递推能推出全局最优。

在时间方面，由于vectors已经创建出来了，与其call对应的method来pop_back()，不如直接定义两个ptr，指向最尾。这样时间花费更少。
*/