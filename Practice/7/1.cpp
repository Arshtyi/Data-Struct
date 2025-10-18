#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int l, r;
};
Node t1[] = {{0, 0}, {0, 2}, {0, 3}, {0, 0}}, t2[] = {{0, 0}, {2, 3}, {0, 4}, {0, 5}, {0, 0}, {0, 0}};
void pre_order(Node t[], int u)
{
    cout << u << " ";
    if (t[u].l)
        pre_order(t, t[u].l);
    if (t[u].r)
        pre_order(t, t[u].r);
}
void in_order(Node t[], int u)
{
    if (t[u].l)
        in_order(t, t[u].l);
    cout << u << " ";
    if (t[u].r)
        in_order(t, t[u].r);
}
void post_order(Node t[], int u)
{
    if (t[u].l)
        post_order(t, t[u].l);
    if (t[u].r)
        post_order(t, t[u].r);
    cout << u << " ";
}
void level_order(Node t[], int n)
{
    if (!n)
        return;
    queue<int> q;
    q.push(n);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << u << " ";
        if (t[u].l)
            q.push(t[u].l);
        if (t[u].r)
            q.push(t[u].r);
    }
}
signed main()
{
    cout << "Tree 1 Traversals:\n";
    cout << "Pre-order: ";
    pre_order(t1, 1);
    cout << "\nIn-order: ";
    in_order(t1, 1);
    cout << "\nPost-order: ";
    post_order(t1, 1);
    cout << "\nLevel-order: ";
    level_order(t1, 1);
    cout << "\n\nTree 2 Traversals:\n";
    cout << "Pre-order: ";
    pre_order(t2, 1);
    cout << "\nIn-order: ";
    in_order(t2, 1);
    cout << "\nPost-order: ";
    post_order(t2, 1);
    cout << "\nLevel-order: ";
    level_order(t2, 1);
    cout << endl;
    return 0;
}
