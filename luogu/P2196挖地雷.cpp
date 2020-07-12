#include <bits/stdc++.h>
using namespace std;
int n;
int s[101];
bool a[31][31];
bool is[101];
int ans = 0, ss[101], ct = 0, tp[101], ttp = 0;
void dfs(int node, int sum)
{
    if (ans < sum)
    {
        ans = sum;
        for (int i = 1; i <= ttp; i++)
            ss[i] = tp[i];
        ct = ttp;
    }
    for (int i = 1; i <= n; i++)
        if (!is[i] && a[node][i] == 1)
        {
            is[i] = 1;
            tp[++ttp] = i;
            dfs(i, sum + s[i]);
            --ttp;
            is[i] = 0;
        }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &s[i]);
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
    {
        is[i] = 1;
        tp[++ttp] = i;
        dfs(i, s[i]);
        ttp--;
        is[i] = 0;
    }
    for (int i = 1; i <= ct; i++)
    {
        printf("%d ", ss[i]);
    }
    printf("\n%d", ans);
    return 0;
}