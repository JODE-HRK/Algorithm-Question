#include <bits/stdc++.h>
#define R register
#define mp make_pair
#define ll long long
#define pii pair<int, int>
#define pli pair<ll, int>
using namespace std;
const int N = 210000;
const ll inf = 1e12;

int n, m, s, t, vis[N];
ll f[N], g[N], ans = inf;
vector<pii> to[N], rto[N];
struct point
{
    ll x, y;
    point(ll x, ll y) : x(x), y(y) {}
    inline point operator-(const point &a) const
    {
        return point(x - a.x, y - a.y);
    }
    inline ll cross(const point &a) const
    {
        return x * a.y - y * a.x;
    }
};
vector<point> hull;

inline void dijk(int s, vector<pii> *to, ll *dis)
{
    priority_queue<pli, vector<pli>, greater<pli>> que;
    for (R int i = 1; i <= n; ++i)
        dis[i] = inf, vis[i] = 0;
    que.push(mp(dis[s] = 0, s));
    while (que.size())
    {
        int now = que.top().second;
        que.pop();
        if (vis[now])
            continue;
        vis[now] = 1;
        for (auto &v : to[now])
            if (dis[v.first] > dis[now] + v.second)
                que.push(mp(dis[v.first] = dis[now] + v.second, v.first));
    }
    return;
}

int main()
{
    int x, y, w;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> s >> t;
    while (m--)
    {
        cin >> x >> y >> w;
        to[x].push_back(mp(y, w));
        rto[y].push_back(mp(x, w));
    }
    dijk(s, to, f), dijk(t, rto, g);
    for (R int i = 1; i <= n; ++i)
    {
        point tmp(i, (ll)i * i + g[i]);
        while (hull.size() >= 2)
        {
            auto r = prev(hull.end()), l = prev(r);
            if ((tmp - *l).cross(*r - *l) < 0)
                break;
            hull.pop_back();
        }
        hull.push_back(tmp);
    }
    auto tl = hull.begin();
    for (R int i = 1; i <= n; ++i)
    {
        while (next(tl) != hull.end())
        {
            auto v = next(tl);
            if ((*v - *tl).cross(point(1, 2 * i)) < 0)
                break;
            ++tl;
        }
        ans = min(ans, f[i] + (ll)i * i + tl->y - 2ll * i * tl->x);
    }
    cout << ans << endl;
    return 0;
}