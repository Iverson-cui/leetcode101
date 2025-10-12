#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL)
    {
    }
};

int main()
{
    int num;
    cin >> num;
    // head and p are all pointers. They point to the same location.
    ListNode *head = new ListNode(num);
    ListNode *p = head;

    // 利用尾插法创建一个链表
    while (cin >> num)
    {
        ListNode *q = new ListNode(num);
        p->next = q;
        p = p->next;
    }

    // 遍历这个链表，并输出每个结点的元素
    ListNode *m = head;
    while (m != nullptr)
    {
        cout << m->val << endl;
        m = m->next;
    }

    return 0;
}
