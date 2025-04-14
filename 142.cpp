#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *detectCycle(ListNode *head)
{
    ListNode *slow = head, *fast = head;
    bool is_first_cycle = true;
    // 检查环路。
    while (fast != slow || is_first_cycle)
    {
        if (fast == nullptr || fast->next == nullptr)
        {
            return nullptr;
        }
        fast = fast->next->next;
        slow = slow->next;
        is_first_cycle = false;
    }
    // 寻找节点。
    fast = head;
    while (fast != slow)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return fast;
}

/*
寻找环路问题使用快慢指针解法，又叫Floyd判圈法。快指针走2步，慢指针走1步。如果存在环路，则快慢指针一定会相遇且在环路内部相遇。
快指针走2步的原因是：快指针相对慢指针每次都多走一步，这样迟早快慢会碰上。但是如果快指针走3步，慢指针走1步，有可能会出现快指针绕过慢指针的情况，处理起来很复杂。走2步是一定能碰上的，因为相对速度是1
当碰上的时候，快指针走的距离是慢的2倍，且两者距离相差为环路长度的倍数。所以慢指针走的长度就是环路长度的倍数。
设慢指针进入环路之前走的长度为x，进入环路之后走的长度为y，则x+y=NC。
慢指针现在距离环路入口的距离为y，故慢指针再走x就走到了环路的入口。但是我们不知道具体的x是多少。所以将快指针移动到list的head，让快指针和慢指针一起往前走，都走1步。这样x步后，2个指针一起走到了head的位置，这个位置就是环路的入口。
*/