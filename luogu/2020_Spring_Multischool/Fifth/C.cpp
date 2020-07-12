#include <bits/stdc++.h>
using namespace std;
int n, m;
int vis[30]; //这个数组仅标记右侧端点
int g[30][30], cz[30], cy[30];
int point(int u)
{
    for (int i = 1; i <= n; i++)
    {
        if (g[u][i] && !vis[i])
        {
            vis[i] = 1;
            if (cy[i] == -1 || point(cy[i]))
            {
                cz[u] = i;
                cy[i] = u;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    memset(g, 0, sizeof(g));
    cin >> n;
    int u, v;
    string s;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &m);
        u = i;
        while (m--)
        {
            cin >> s;
            v = s[0] - 'a' + 1;
            g[u][v] = 1;
        }
    }
    memset(cz, -1, sizeof(cz));
    memset(cy, -1, sizeof(cy));
    int ret = 0;
    for (int i = 1; i <= n; i++)
    {
        if (cz[i] == -1)
        {
            memset(vis, 0, sizeof(vis));
            ret += point(i);
        }
    }
    if (ret == n)
        printf("Yes");
    else
        printf("No");
    return 0;
}
