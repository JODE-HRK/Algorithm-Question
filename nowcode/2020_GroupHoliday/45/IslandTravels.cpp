/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-08 19:58:09
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-08 20:22:56
 */
#include <bits/stdc++.h>
using namespace std;
int MoveX[4] = {1, 0, -1, 0};
int MoveY[4] = {0, 1, 0, -1};
int R, C, sum = 0, ans = 0x7fffffff;
char M[51][51];
struct op
{
    int x, y;
};
queue<op> ST;
queue<pair<op, int>> Q;
int dis[51][51];
void bfs()
{
    while (!Q.empty())
    {
        op now = Q.front().first;
        int nowdis = Q.front().second;
        Q.pop();
        for (int i = 0; i < 4; i++)
        {
            int xx = now.x + MoveX[i], yy = now.y + MoveY[i];
            if (xx <= 0 || xx > R || yy <= 0 || yy > C || M[xx][yy] == '.' || dis[xx][yy] == 0x7fffffff)
                continue;
            op tmp;
            tmp.x = xx, tmp.y = yy;
            if (M[xx][yy] == 'S')
                Q.push(make_pair(tmp, nowdis + 1));
            else
                Q.push(make_pair(tmp, nowdis));
        }
    }
}
int main()
{
    scanf("%d %d", &R, &C);
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
        {
            cin >> M[i][j];
            if (M[i][j] == 'X')
                ST.push((op){i, j}), sum++;
        }
    while (!ST.empty())
    {
        op now = ST.front();
        memset(dis, 0x7fffffff, sizeof(dis));
        dis[now.x][now.y] = 0;
        Q.push(make_pair(now, 0));
        bfs();
        ST.pop();
    }
}