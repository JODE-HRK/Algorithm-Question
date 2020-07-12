#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <vector>
#include <ctime>
using namespace std;
using namespace std;
int n, zans = 0;
struct ca
{
    int up = 0, down = 0, left = 0, right = 0;
    int sum = 4;
} g[101][101];
void dfs(int ans)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (g[i][j].sum > 1)
            {
                if (g[i][j + 1].left == 0 && g[i][j].right == 0 && g[i][j + 1].sum > 1)
                {
                    g[i][j + 1].left = 1, g[i][j].right = 1;
                    g[i][j].sum--, g[i][j + 1].sum--;
                    return dfs(ans + 1);
                }
                else if (g[i][j].left == 0 && g[i][j - 1].right == 0 && g[i][j - 1].sum > 1)
                {
                    g[i][j].left = 1, g[i][j - 1].right = 1;
                    g[i][j].sum--, g[i][j - 1].sum--;
                    return dfs(ans + 1);
                }
                else if (g[i][j].up == 0 && g[i - 1][j].down == 0 && g[i - 1][j].sum > 1)
                {
                    g[i][j].up = 1, g[i - 1][j].down = 1;
                    g[i][j].sum--, g[i - 1][j].sum--;
                    return dfs(ans + 1);
                }
                else if (g[i][j].down == 0 && g[i + 1][j].up == 0 && g[i + 1][j].sum > 1)
                {
                    g[i][j].down = 1, g[i + 1][j].up = 1;
                    g[i][j].sum--, g[i + 1][j].sum--;
                    return dfs(ans + 1);
                }
            }
        }
    }
    zans = max(zans, ans);
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < 2 * n; i++)
        for (int j = 1; j < 2 * n; j++)
        {
            char c = getchar();
            while (c != '*' && c != '-' && c != '|' && c != '.')
                c = getchar();
            if (i % 2)
            {
                if (c == '-')
                    g[i / 2][j / 2].down = 1, g[i / 2 + 1][j / 2].up = 1, g[i / 2][j / 2].sum--, g[i / 2 + 1][j / 2].sum--;
            }
            else
            {
                if (c == '|')
                    g[i / 2][j / 2].right = 1, g[i / 2][j / 2 + 1].left = 1, g[i / 2][j / 2].sum--, g[i / 2][j / 2 + 1].sum--;
            }
        }
    dfs(0);
    printf("%d", zans + 1);
    // for (int i = 1; i < n; i++)
    // {
    //     for (int j = 1; j < n; j++)
    //         printf("%d ", g[i][j].sum);
    //     cout << endl;
    // }
    return 0;
}