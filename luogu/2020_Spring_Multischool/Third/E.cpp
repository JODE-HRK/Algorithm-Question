#include <bits/stdc++.h>
using namespace std;
const int maxn = 502;
int n, m;
bool g[maxn][maxn];
int s[2 * maxn];
const int fx[3][4] = {{0, 1, 1, 2}, {0, 1, 1, 2}, {0, 0, 1, 1}};
const int fy[3][4] = {{0, 0, 1, 1}, {0, 0, -1, -1}, {0, 1, 0, -1}};
int col[maxn];
vector<pair<int, int>> ans;
int sum = 0;
int X, Y;
bool check()
{ //使用最优策略，一定能被放进去
    bool tmp[maxn][maxn];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            tmp[i][j] = g[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (tmp[i][j])
            {
                int tp = tmp[i][j + 1] ? 2 : 1; // 判断是放入B还是C
                for (int k = 0; k < 4; ++k)
                    if (!tmp[i + fx[tp][k]][j + fy[tp][k]])
                        return false;
                for (int k = 0; k < 4; ++k)
                    tmp[i + fx[tp][k]][j + fy[tp][k]] = 0;
            }
    return true;
}
bool cmp(pair<int, int> x, pair<int, int> y)
{
    return x.first != y.first ? x.first < y.first : x.second < y.second;
}
int main()
{
    memset(g, 0, sizeof(g));
    scanf("%d %d", &n, &m);
    fill(col + 1, col + 1 + n, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            char tp = getchar();
            while (tp > '1' || tp < '0')
                tp = getchar();
            g[i][j] = tp - '0';
            if (g[i][j])
                sum++, s[i + j]++; //sum记录空格总数，s记录对角线的特征(左下到右上的对角线)
        }
    int tmp;
    for (int i = 2; i <= n + n; i++)
    {
        if (s[i] & 1)
        { //观察三种图形之后得出结论，记录对角线上的为奇数时，A图形一定在该对角线上
            tmp = i;
            break;
        }
    }
    for (int i = 1, j = tmp - 1; i < tmp; i++, j--)
        if (i <= n && j <= m)
        {
            bool mk = true;
            for (int k = 0; k < 4; k++)
                if (!g[i + fx[0][k]][j + fy[0][k]])
                {
                    mk = false;
                    break;
                }
            if (mk)
            {
                for (int k = 0; k < 4; k++)
                    g[i + fx[0][k]][j + fy[0][k]] = 0;
                if (check())
                    ans.push_back({i, j});
                for (int k = 0; k < 4; k++)
                    g[i + fx[0][k]][j + fy[0][k]] = 1;
            }
        }
    sort(ans.begin(), ans.end(), cmp);
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
        printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}