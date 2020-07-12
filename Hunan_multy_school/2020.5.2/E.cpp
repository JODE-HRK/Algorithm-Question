#include <bits/stdc++.h>
using namespace std;
int t, n, p;
struct Node
{
    int x;
    Node *nxt, *pre;
    Node(int xx)
    {
        x = xx;
        nxt = NULL;
        pre = NULL;
    };
};
bool judge(int xs)
{
    while (xs > 1)
    {
        if (xs % 2)
            return 0;
        xs /= 2;
    }
    return 1;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        int zp = 0;
        Node *head = NULL, *tail = NULL;
        string ans;
        scanf("%d", &n);
        while (n--)
        {
            scanf("%d", &p);
            zp += p;
            Node *tp = new Node(p);
            if (head == NULL)
                head = tail = tp, ans += 'r';
            else if (head->x == p)
            {
                head->x += p;
                while (head != tail && head->x == head->nxt->x)
                    head->nxt->x += head->x, head = head->nxt;
                ans += 'l';
            }
            else if (tail->x == p)
            {
                tail->x += p;
                while (head != tail && tail->x == tail->pre->x)
                    tail->pre->x += tail->x, tail = tail->pre;
                ans += 'r';
            }
            else if (head->x < p || head == tail || (tail->x > p && tail->x - p <= head->x - p))
            {
                tp->pre = tail, tail->nxt = tp, tail = tail->nxt;
                ans += 'r';
            }
            else
            {
                head->pre = tp;
                tp->nxt = head, head = tp, ans += 'l';
            }
            // cout << head->x << endl;
        }
        // cout << ans << endl;
        if (head == tail && judge(zp))
            cout << ans << endl;
        else
            printf("no\n");
    }
    return 0;
}