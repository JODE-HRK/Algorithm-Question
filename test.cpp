#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t, n, x;
int g[201][201];
int used[201], col[201];
bool found(int x)
{
    for (int i = 1; i <= n; i++)
    {
        if (g[x][i] && !used[i])
        {
            used[i] = 1;
            if (!col[i] || found(col[i]))//如果我要匹配的被匹配了，就再找上一个匹配到它的还有没有其他选择
            {
                col[i] = x; //记录为我当前匹配的
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    cin >> t;
    while (t--)
    {
        scanf("%d", &n);
        memset(g, 0, sizeof(g));
        fill(col, col + (1 + n), 0);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                scanf("%d", &x);
                if (x)
                    g[i][j] = 1;
            }
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            fill(used, used + 1 + n, 0);
            if (found(i))
                sum++;
        }
        if (sum == n)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}