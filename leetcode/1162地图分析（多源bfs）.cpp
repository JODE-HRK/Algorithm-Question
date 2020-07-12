#include <bits/stdc++.h>
using namespace std;
int g[101][101], n;
bool vis[101][101];
int X[4] = {0, 1, 0, -1};
int Y[4] = {1, 0, -1, 0};
struct OP
{
    int x, y, cnt;
};
queue<OP> Q;
int bfs()
{
    int ans = -1;
    while (!Q.empty())
    {
        int xx = Q.front().x, yy = Q.front().y, s = Q.front().cnt;
        Q.pop();
        for (int i = 0; i < 4; i++)
        {
            int ix = xx + X[i], iy = yy + Y[i];
            if (ix < 0 || ix >= n || iy < 0 || iy >= n)
                continue;
            if (!vis[ix][iy] && !g[ix][iy])
            {
                Q.push({ix, iy, s + 1});
                ans = max(s + 1, ans);
                vis[ix][iy] = 1;
            }
        }
    }
    return ans;
}
int pre()
{
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (g[i][j] == 1)
            {
                vis[i][j] = 1;
                Q.push({i, j, 0});
            }
    return bfs();
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);
    printf("%d", pre());
    return 0;
}