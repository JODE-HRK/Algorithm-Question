#include <bits/stdc++.h>
using namespace std;
int n, sx, sy, tx, ty;
const int fx[8] = {1, -1, 0, 0, 1, 1, -1, -1}, fy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
const int maxn = 1e8 + 7;
struct Node
{
    int x, y;
} q[maxn];
queue<Node> Q;
map<int, map<int, int>> P;
int gcd(int x, int y)
{
    return y ? gcd(y, x % y) : x;
}
bool judge(int x, int y)
{
    return x >= 1 && x <= n && y >= 1 && y <= n && gcd(x, y) != 1;
}
bool bfs(int x, int y, int tp)
{
    while (!Q.empty())
        Q.pop();
    Q.push({x, y});
    P[x][y] = tp;
    while (!Q.empty())
    {
        int nowx = Q.front().x, nowy = Q.front().y;
        Q.pop();
        if (nowx == nowy)
            return 1;
        for (int i = 0; i < 8; i++)
        {
            int xx = nowx + fx[i], yy = nowy + fy[i];
            if (judge(xx, yy))
            {
                if (!P[xx][yy])
                {
                    if (xx == yy)
                        return 1;
                    else
                        Q.push({xx, yy}), P[xx][yy] = tp;
                }
                else if (P[xx][yy] != P[nowx][nowy])
                    return 1;
            }
        }
    }
    return 0;
}
int main()
{
    scanf("%d", &n);
    scanf("%d %d %d %d", &sx, &sy, &tx, &ty);
    if (bfs(sx, sy, 1) && bfs(tx, ty, 2))
        printf("gl");
    else
        printf("gg");

    return 0;
}