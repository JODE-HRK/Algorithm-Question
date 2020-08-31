/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-27 12:40:47
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-30 22:55:12
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 7;
int n, m, block;
int b[maxn], c[maxn];
struct PRO
{
    int l, r, id, blo;
    bool operator<(const PRO x) const
    {
        if (blo == x.blo)
            return r < x.r;
        return blo < x.blo;
    }
} pro[maxn];

queue<int> G;
bool vis[maxn];
int ans = 0;
int l = 1, r = 0;
void change()
{
    while (!G.empty())
    {
        int x = G.front();
        vis[x] = 0;
        G.pop();
        if (c[x] == 1)
        {
            ans = x;
            return;
        }
    }
}
void pre(int i)
{
    while (pro[i].r > r)
    {
        ++r, ++c[b[r]];
        if (c[b[r]] == 1)
        {
            ans = b[r];
            if (!vis[ans])
                G.push(ans), vis[ans] = 1;
        }
        else if (ans == b[r])
        {
            ans = 0;
            change();
        }
    }
    while (pro[i].l > l)
    {
        ++c[b[l]];
        if (c[b[l]] == 1)
        {
            ans = b[l];
            if (!vis[ans])
                G.push(ans), vis[ans] = 1;
        }
        else if (ans == b[l])
        {
            ans = 0;
            change();
        }
        ++l;
    }
    while (pro[i].r < r)
    {
        c[b[r]]--;
        if (c[b[r]] == 1)
        {
            ans = b[r];
            if (!vis[ans])
                G.push(ans), vis[ans] = 1;
        }
        else if (ans == b[r])
        {
            ans = 0;
            change();
        }
        r--;
    }
    while (pro[i].l < l)
    {
        --l, c[b[l]]--;
        if (c[b[l]] == 1)
        {
            ans = b[l];
            if (!vis[ans])
                G.push(ans), vis[ans] = 1;
        }
        else if (ans == b[l])
        {
            ans = 0;
            change();
        }
    }
}
int zans[maxn];
int main()
{
    scanf("%d", &n);
    block = sqrt(n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    // root[0] = build(1, n);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%d %d", &pro[i].l, &pro[i].r), pro[i].id = i, pro[i].blo = (pro[i].l - 1) / block + 1;
    sort(pro + 1, pro + 1 + m);
    for (int i = 1; i <= m; i++)
    {
        pre(i);
        // printf("YES\n");
        zans[pro[i].id] = ans;
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", zans[i]);
    return 0;
}