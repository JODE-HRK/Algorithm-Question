#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e6 + 7;
int n;
int side[maxn][2];
int target[maxn];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &side[i][0], &side[i][1]);
    target[0] = 1;
    target[1] = side[1][1];
    int sl[maxn], sr[maxn];
    sl[0] = sr[0] = 0;
    for (int i = 1; i < n - 1; i++)
    {
        sl[i] = sr[i] = 0;
        if (target[i - 1] == side[target[i]][0])
            target[i + 1] = side[target[i]][1];
        else if (target[i - 1] == side[target[i]][1])
            target[i + 1] = side[target[i]][0];
        else
        {
            printf("-1");
            return 0;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        sl[(target[i] - i - 1 + n) % n]++;
        sr[(target[i] - (n - i) + n) % n]++;
    } //sl[i]和sr[i]都是统计的目标串中每个数对于初始串的距离，正反统计
    for (int i = 0; i < n; i++)
        ans = max(ans, max(sl[i], sr[i]));
    printf("%d", n - ans);
    return 0;
}
/*
6
4 3
1 2
3 5
2 6
5 4
6 1
*/