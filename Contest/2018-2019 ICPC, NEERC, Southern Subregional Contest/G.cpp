#include <bits/stdc++.h>
using namespace std;
const int maxn = 107, inf = 1e9;
int n, m, hpos, flag, minn, maxx;
int num[maxn], hel[maxn], val[maxn], outp[maxn], mark[maxn];
bool judge(int pos)
{
    stack<int> S;
    while (!S.empty())
        S.pop();
    int now = 0, ok = 0;
    for (int i = maxx; i > pos; i--)
    {
        if (now < hel[num[i]])
            now = hel[num[i]], S.push(num[i]);
        now += val[i];
        if (now < 0)
            return false;
    }
    ok |= (now + val[pos] >= 0), now = 0;
    for (int i = minn; i < pos; i++)
    {
        if (now < hel[num[i]])
            now = hel[num[i]], S.push(num[i]);
        now += val[i];
        if (now < 0)
            return false;
    }
    ok |= (now + val[pos] >= 0);
    if (!ok)
        return false;
    printf("%d\n", pos);
    while (!S.empty())
        printf("%d ", S.top()), mark[S.top()] = true, S.pop();
    for (int i = 1; i <= m; i++)
        if (!mark[i])
            printf("%d ", i);
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    hel[0] = -inf, minn = inf, maxx = -inf;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &hpos, &hel[i]), num[hpos] = i;
        minn = min(minn, hpos), maxx = max(maxx, hpos);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1; i <= n; i++)
        if (judge(i))
            return 0;
    printf("-1");
    return 0;
}