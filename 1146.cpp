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

class SnapshotArray
{
    // vector<int> data;
    vector<vector<int>> history_index;
    vector<vector<int>> history_value;
    int snap_id = 0;

public:
    SnapshotArray(int length)
    {
        // data.assign(length, 0);
        history_index.assign(length, vector<int>{0});
        history_value.assign(length, vector<int>{0});
    }

    void set(int index, int val)
    {
        // data[index] = val;
        // has updated in current snap_id
        if (history_index[index].back() == snap_id)
        {
            history_value[index].back() = val;
        }
        else
        {
            history_index[index].push_back(snap_id);
            history_value[index].push_back(val);
        }
    }

    int snap()
    {
        ++snap_id;
        return snap_id - 1;
    }

    int get(int index, int snap_id)
    {
        int tmp = ranges::lower_bound(history_index[index], snap_id) - history_index[index].begin();
        if (tmp == history_index[index].size())
        {
            return history_value[index].back();
        }
        return (history_index[index][tmp] == snap_id) ? history_value[index][tmp] : history_value[index][tmp - 1];
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */

/**
 * 上面的做法也可以，只不过时空不占优势。
 */

class SnapshotArray
{
    unordered_map<int, vector<pair<int, int>>> history; // 每个 index 的历史修改记录
    int cur_snap_id = 0;

public:
    SnapshotArray(int) {}

    void set(int index, int val)
    {
        history[index].emplace_back(cur_snap_id, val);
    }

    int snap()
    {
        return cur_snap_id++;
    }

    int get(int index, int snap_id)
    {
        auto &h = history[index];
        // 找快照编号 <= snap_id 的最后一次修改记录
        // 等价于找快照编号 >= snap_id+1 的第一个修改记录，它的上一个就是答案
        int j = ranges::lower_bound(h, pair(snap_id + 1, 0)) - h.begin() - 1;
        return j >= 0 ? h[j].second : 0;
    }
};

/**
 * 在比较pair的时候，会先比较第一个元素，再比较第二个元素。可以利用这个特点来做binary search。
 * 第二个相比于第一个，使用unordered_map节省了空间，因为没有修改过的index不需要存储。
 */