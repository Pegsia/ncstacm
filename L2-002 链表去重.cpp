#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

const int maxn = 100010;

// 10w以内用静态链表
struct Node
{
    int data; // 数据域
    int next; // 指针域
} node[maxn];

int s, n;        // 链表起始地址, 节点个数
set<int> hasval; // 判断绝对值是否存在

int ans1[maxn]; // 记录去重后的结点的地址
int ans2[maxn]; // 记录被删除的结点的地址
int tot1, tot2; // 记录ans1, ans2的元素个数

int main()
{
    // freopen("/Users/zhbink/Documents/C++/C++/in.txt","r",stdin);
    ios::sync_with_stdio(false);

    cin >> s >> n;

    //  链表题永远先读进node数组中
    for (int i = 0; i < n; i++)
    {
        int address, data, next;
        cin >> address >> data >> next;
        node[address].data = data;
        node[address].next = next;
    }

    //  由首地址s遍历全部结点。 因为题目确定了所有点一开始就是一个链表， 所以一定能遍历全部结点
    for (int add = s; add != -1; add = node[add].next)
    {
        int val = abs(node[add].data);
        if (!hasval.count(val))
        {
            hasval.insert(val);
            // ans1[]存放去重后的元素的地址
            ans1[tot1++] = add;
        }
        else
            // ans2[]存放被删除的元素的地址
            ans2[tot2++] = add;
    }

    for (int i = 0; i < tot1; i++)
    {
        if (i == tot1 - 1)
            printf("%05d %d %d\n", ans1[i], node[ans1[i]].data, -1);
        else
            printf("%05d %d %05d\n", ans1[i], node[ans1[i]].data, ans1[i + 1]);
    }

    for (int i = 0; i < tot2; i++)
    {
        if (i == tot2 - 1)
            printf("%05d %d %d\n", ans2[i], node[ans2[i]].data, -1);
        else
            printf("%05d %d %05d\n", ans2[i], node[ans2[i]].data, ans2[i + 1]);
    }
}