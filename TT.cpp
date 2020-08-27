/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-01 22:50:04
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-20 23:37:20
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 7;
int m, o, cnt = 0, id;
vector<int> Node[maxn];
int a[maxn], pd[maxn], x, fa[maxn];
void push_down(int x)
{
    if (pd[x])
    {
        a[x] += pd[x];
        for (int i = 0; i < Node[x].size(); i++)
        {
            pd[Node[x][i]] += pd[x];
        }
        pd[x] = 0;
    }
}
int main()
{
    memset(a, 0, sizeof(a));
    memset(pd, 0, sizeof(pd));
    scanf("%d", &m);
    while (m--)
    {
        scanf("%d", &o);
        if (o == 1)
        {
            scanf("%d", &id);
            Node[id].push_back(++cnt);
            a[cnt] = 0;
            pd[cnt] = 0;
            fa[cnt] = id;
        }
        else if (o == 2)
        {
            scanf("%d %d", &id, &x);
            pd[id] += x;
        }
        else
        {
            scanf("%d", &id);
            vector<int> tmp;
            tmp.clear();
            while (id > 0)
            {
                tmp.push_back(id);
                id = fa[id];
            }
            tmp.push_back(id);
            for (int i = tmp.size() - 1; i >= 0; i--)
            {
                push_down(tmp[i]);
            }
            printf("%d\n", a[tmp[0]]);
        }
    }
    return 0;
}