    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int maxn = 1005;
    int n, m, g[maxn][maxn], cnt = 0;
    struct P
    {
        int val;
        int a, b;
    } c[maxn * maxn];
    int ch[maxn];
    ll sum = 0, var, ans;
    bool cmp(P x, P y)
    {
        return x.val < y.val;
    }
    ll sqr(ll x)
    {
        return x * x;
    }
    void rep(int a, int b)
    {
        ll nsum = sum + b - a;
        var += 2 * sum * (sum - nsum) - (sum * sum - nsum * nsum) - (ll)a * a * n + (ll)b * b * n + 2 * nsum * (a - b);
        sum = nsum;
        ans = min(ans, var);
    }
    int main()
    {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                scanf("%d", &g[i][j]);
            sort(g[i] + 1, g[i] + 1 + m);
            sum += ch[i] = g[i][1];
            for (int j = 2; j <= m; j++)
                c[++cnt].val = g[i][j] + g[i][j - 1], c[cnt].a = g[i][j - 1], c[cnt].b = g[i][j];
        }
        sort(c + 1, c + 1 + cnt, cmp);
        for (int i = 1; i <= n; i++)
            var += sqr(1ll * ch[i]) * n - 2ll * ch[i] * sum;
        var += sum * sum;
        ans = var;
        for (int i = 1; i <= cnt; i++)
            rep(c[i].a, c[i].b);
        printf("%lld", ans);
        return 0;
    }