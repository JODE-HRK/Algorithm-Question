/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-13 21:35:45
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-18 15:20:21
 */
#include <bits/stdc++.h>
#define ll long long
#define inf 0x7fffffff
#define INF 1000000000000ll
#define pii pair<int, int>
#define pll pair<ll, ll>
const int maxn = 8e5 + 7;
using namespace std;
inline int read()
{
    int x = 0;
    char c = getchar();
    while (c > '9' || c < '0')
        c = getchar();
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x;
}
int n, m;
int fa[maxn];
// bool vis[maxn];
list<int> node[maxn];
void init()
{
    for (int i = 0; i < n; i++)
    {
        node[i].clear();
        // vis[i] = 0;
        fa[i] = i;
    }
}
void addEdge(int x, int y)
{
    node[x].push_back(y);
}
int Find(int x)
{
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}
void add(int color)
{
    int s = node[color].size();
    while (s--)
    {
        list<int>::iterator it;
        it = node[color].begin();
        int tmp = Find(*it);
        node[color].erase(it);
        if (tmp != color)
        {
            // int ss = node[tmp].size();
            node[color].splice(node[color].end(), node[tmp]);
            fa[Find(tmp)] = color;
        }
    }
}
int main()
{
    // freopen(".in", "r", stdin);
    int t;
    t = read();
    while (t--)
    {
        n = read(), m = read();
        init();
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            x = read(), y = read();
            addEdge(x, y);
            addEdge(y, x);
        }
        int q;
        q = read();
        while (q--)
        {
            int o;
            o = read();
            if (Find(o) == o)
                add(Find(o));
        }
        for (int i = 0; i < n; i++)
            printf("%d ", Find(i));
        cout << endl;
    }
    return 0;
}
/*
1
5 5
0 1
0 2
1 2
1 3
3 4
3
4 4 0

1
4 3
0 1
1 2
2 3
4
0 1 3 0
*/