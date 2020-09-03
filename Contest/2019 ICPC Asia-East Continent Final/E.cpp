#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 7;
int n, m;
int head[maxn], tot;
int f[maxn][32];
struct Edge
{
    int to, val, nxt;
} edge[maxn << 1];
vector<ll> G[maxn];
ll cost[maxn];
ll cnt, dis;

void add(int x, int y, int z)
{
    edge[tot] = (Edge){y, z, head[x]};
    head[x] = tot++;
}

void dfs(int now, int fa, int dep)
{
    if (now == n)
    {
        dis = dep;
        return;
    }
    for (int i = head[now]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to, w = edge[i].val;
        if (v == fa)
            continue;
        G[cnt].push_back(w);
        dfs(v, now, dep + 1);
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    fill(head, head + 1 + n, -1);
    ll sum = 0;
    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add(x, y, z);
        sum += z;
    }

    cnt = 0;
    for (int i = head[1]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        cnt++;
        G[cnt].push_back(edge[i].val);
        dfs(v, 1, 1);
        sort(G[cnt].begin(), G[cnt].end()); //逐步补满时好算一点
        int k = 0;
        while (k < dis - 1)
        {
            cost[k + 1] += G[cnt][k + 1] - G[cnt][k]; //每一层补满需要多少
            k++;
        }
        sum -= G[cnt][0] * dis; //最基本的肯定要补满
    }
    // printf("%d\n", dis);
    ll ans = 0;
    for (int i = 1; i < dis; i++)
    {
        if (sum < dis) //无法继续补了就退出
            break;
        ll tmp = min(1ll * (sum / dis), cost[i]); //换算成第i层补满需要多少
        ans += tmp * i;
        sum -= tmp * dis;
    }
    // printf("YES\n");
    printf("%lld\n", ans);
    return 0;
}
