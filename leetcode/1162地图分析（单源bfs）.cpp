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
    while (!Q.empty())
    {
        int xx = Q.front().x, yy = Q.front().y, s = Q.front().cnt;
        Q.pop();
        for (int i = 0; i < 4; i++)
        {
            int ix = xx + X[i], iy = yy + Y[i];
            if (ix < 0 || ix >= n || iy < 0 || iy >= n)
                continue;
            if (g[ix][iy])
                return s + 1;
            if (!vis[ix][iy])
            {
                Q.push({ix, iy, s + 1});
                vis[ix][iy] = 1;
            }
        }
    }
    return 0;
}
int pre()
{
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (g[i][j] == 0)
            {
                while (!Q.empty())
                    Q.pop();
                memset(vis, 0, sizeof(vis));
                vis[i][j] = 1;
                Q.push({i, j, 0});
                ans = max(bfs(), ans);
            }
    return ans;
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