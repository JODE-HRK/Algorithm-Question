#include <bits/stdc++.h>
using namespace std;
int n, k;
int x[21];
bool b[21];
int ans = 0;
bool isprime(int x)
{
    if (x <= 1)
        return false;
    if (~x & 1 || x % 3 == 0)
        return x <= 3;
    for (int i = 5, j = 2; i * i <= x; i += j, j = j == 2 ? 4 : 2)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}
void dfs(int sum, int cnt, int nxt)
{
    if (cnt == k)
    {
        if (isprime(sum))
            ans++;
        return;
    }
    for (int i = nxt; i <= n; i++)
        if (!b[i])
        {
            b[i] = 1;
            dfs(sum + x[i], cnt + 1, i);
            b[i] = 0;
        }
}
int main()
{
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &x[i]);
    dfs(0, 0, 1);
    printf("%d", ans);
    return 0;
}