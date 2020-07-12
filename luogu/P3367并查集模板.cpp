#include <bits/stdc++.h>
using namespace std;
int n, m;
int fa[10001];
int z, x, y;
int find(int a)
{
    if (fa[a] == a)
        return a;
    return fa[a] = find(fa[a]);
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &z, &x, &y);
        if (z == 2)
        {
            if (find(x) == find(y))
                printf("Y\n");
            else
                printf("N\n");
        }
        else
            fa[find(x)] = find(y);
    }
    return 0;
}
