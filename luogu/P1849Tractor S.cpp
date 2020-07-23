//BFS加优先队列优化
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, xs, ys;
bool block[1010][1010];
int X[4] = {0, -1, 0, 1};
int Y[4] = {1, 0, -1, 0};
struct node
{
    int x, y, val;
    bool operator<(const node &x) const
    {
        return x.val < val;
    }
};
int bfs()
{
    bool vis[1010][1010];
    // memset(vis, 0, sizeof(vis));
    vis[xs][ys] = 1;
    priority_queue<node> Q;
    while (!Q.empty())
        Q.pop();
    Q.push((node){xs, ys, 0});
    while (!Q.empty())
    {
        node now = Q.top();
        Q.pop();
        if (now.x == 0 && now.y == 0)
            return now.val;
        for (int i = 0; i < 4; i++)
        {
            int xx = now.x + X[i], yy = now.y + Y[i], tmpval;
            if (xx < 0 || xx > 1007 || yy < 0 || yy > 1007 || vis[xx][yy])
                continue;
            if (block[xx][yy])
                tmpval = now.val + 1;
            else
                tmpval = now.val;
            vis[xx][yy] = 1;
            Q.push((node){xx, yy, tmpval});
        }
    }
}
int main()
{
    // freopen(".in", "r", stdin);
    // memset(block, 0, sizeof(block));
    scanf("%d %d %d", &n, &xs, &ys);
    for (int i = 1; i <= n; i++)
    {
        int sx, sy;
        scanf("%d %d", &sx, &sy);
        block[sx][sy] = 1;
        // cout << i << endl;
    }
    // cout << "yes" << endl;
    printf("%d", bfs());
    return 0;
}