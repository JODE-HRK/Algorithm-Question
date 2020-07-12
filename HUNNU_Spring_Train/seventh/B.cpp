#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn = 2e5 + 7;
int n, t, s;
int b[maxn], dis[maxn];
bool p[maxn];
queue<int> Q;
void init()
{
    fill(dis, dis + maxn, 0x7fffffff);
    fill(p, p + maxn, false);
    cin >> n >> t;
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    dis[0] = 0;
    p[0] = 1;
}
int main()
{
    cin >> s;
    while (s--)
    {
        init();
        Q.push(0); //起始点为0
        while (!Q.empty())
        {
            int now = Q.front();
            p[now] = 0;
            Q.pop();
            for (int i = 1; i <= n; i++)
            {
                int tp = now + b[i];
                if (tp < 0)
                    tp = 0;
                if (tp > 3600)
                    tp = 3600;
                if (dis[tp] > dis[now] + 1)
                {
                    dis[tp] = dis[now] + 1;
                    if (!p[tp])
                        Q.push(tp);
                    p[tp] = true;
                }
            }
        }
        for (int i = t;; i++)
            if (dis[i] != 0x7fffffff)
            {
                cout << dis[i] << ' ' << i - t << endl;
                break;
            }
    }
    return 0;
}