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
    int maximumWhiteTiles(vector<vector<int>> &tiles, int carpetLen)
    {
        int len = tiles.size();
        sort(tiles.begin(), tiles.end());
        int res = 0;
        int left = 0;
        int right = 0;
        int currentCover = 0;
        int currentWhite = 0;
        while ((right < len) && (left <= right))
        {
            printf("left=%d right=%d currentCover=%d currentWhite=%d res=%d\n", left, right, currentCover, currentWhite, res);
            // fully cover next group
            if (carpetLen - currentCover >= (tiles[right][1] - tiles[right][0] + 1))
            {
                if (right == len - 1)
                {
                    printf("reach the end\n");
                    currentWhite += tiles[right][1] - tiles[right][0] + 1;
                    res = max(res, currentWhite);
                    break;
                }
                printf("fully cover tile %d-%d\n", tiles[right][0], tiles[right][1]);
                currentCover += tiles[right + 1][0] - tiles[right][0];
                currentWhite += tiles[right][1] - tiles[right][0] + 1;
                res = max(res, currentWhite);
                printf("currentCover=%d currentWhite=%d res=%d\n", currentCover, currentWhite, res);
                ++right;
            }
            // partially cover next group
            else if (currentCover <= carpetLen)
            {
                printf("partially cover tile %d-%d\n", tiles[right][0], tiles[right][1]);

                currentWhite += carpetLen - currentCover;
                res = max(res, currentWhite);
                printf("res=%d\n", res);
                ++left;
                currentCover -= tiles[left][0] - tiles[left - 1][0];
                printf("current cover from %d to %d\n", currentCover + tiles[left][0] - tiles[left - 1][0], currentCover);
                currentWhite -= (tiles[left - 1][1] - tiles[left - 1][0] + 2);
                printf("currentWhite from %d to %d\n", currentWhite + (tiles[left - 1][1] - tiles[left - 1][0] + 1), currentWhite);
            }
            // gap is so big that can't reach to the next group
            else
            {
                printf("gap too big, move left pointer %d\n", left);
                currentWhite = 0;
                ++left;
                currentCover = 0;
            }
        }
        return max(res, currentWhite);
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> tiles = {{1, 5}, {10, 11}, {12, 18}, {20, 25}, {30, 32}};
    int carpetLen = 10;
    cout << sol.maximumWhiteTiles(tiles, carpetLen) << endl;
    return 0;
}

/**
 * 这种题都是观察到规律，即毯子的放置要么左边在一个tile的左端点，要么右边在一个tile的右端点。所以直接遍历所有的可能放置的情况即可。按照滑动窗口的方法，上面是左边对齐，但是有bug。下面是右边对齐。2种方法思路一直，都是需要判断3种情况：当前left指针对应的tiles能完全覆盖；当前left指针对应的tiles能部分覆盖；当前left指针对应的tiles一点也不能覆盖。第三种情况通过tiles[left][1]和carpet_left的比较来判断。而前两种情况用一个max来处理，即判断tiles[left]里面有多少是无法被覆盖的。如果小于0，就说明都能被覆盖，否则就减去差。
 * 这种题看上去是定滑窗，给出carpet len，但实际上用动滑窗的方法才能更快的求解。定滑窗枚举也可以，但很慢。
 */

class Solution
{
public:
    int maximumWhiteTiles(vector<vector<int>> &tiles, int carpetLen)
    {
        ranges::sort(tiles, {}, [](auto &t)
                     { return t[0]; });
        int ans = 0, cover = 0, left = 0;
        for (auto &tile : tiles)
        {
            int tl = tile[0], tr = tile[1];
            cover += tr - tl + 1; // 统计完整区间长度和

            int carpet_left = tr - carpetLen + 1; // 毯子左端点
            while (tiles[left][1] < carpet_left)
            { // tiles[left] 完全不在窗口中
                cover -= tiles[left][1] - tiles[left][0] + 1;
                left++;
            }

            // tiles[left] 中的小于 carpet_left 的这部分不在窗口中
            int uncover = max(carpet_left - tiles[left][0], 0);
            ans = max(ans, cover - uncover); // 注意这里没有修改 cover，cover 始终是完整区间长度和
        }
        return ans;
    }
};