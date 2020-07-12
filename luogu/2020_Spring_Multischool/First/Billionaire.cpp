#include <bits/stdc++.h>
using namespace std;
int getId(int y, int m, int d)
{
    if (m < 3)
    {
        y--;
        m += 12;
    }
    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * (m - 3) + 2) / 5 + d - 307;
}
vector<int> date(int id)
{
    int x = id + 1789995, n, i, j, y, m, d;
    n = 4 * x / 146097;
    x -= (146097 * n + 3) / 4;
    i = (4000 * (x + 1)) / 1461001;
    x -= 1461 * i / 4 - 31;
    j = 80 * x / 2447;
    d = x - 2447 * j / 80;
    x = j / 11;
    m = j + 2 - 12 * x;
    y = 100 * (n - 49) + i + x;
    return vector<int>({y, m, d});
}
void work()
{
    int M, y, m, d;
    scanf("%d%d%d%d", &M, &y, &m, &d);
    int id = getId(y, m, d);
    int l = 0, r = sqrt(2e9);
    while (l < r)
    {
        int mid = (l + r) / 2;
        int v = M + (0 + mid) * (mid + 1) / 2;
        if (v >= 1000000000)
            r = mid;
        else
            l = mid + 1;
    } //二分法得出向后多少天
    id += l;
    auto ret = date(id); //这个vector的用法好帅！
    printf("%d %d %d\n", ret[0], ret[1], ret[2]);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
}