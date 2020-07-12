int getTheWeek(int year, int month, int day) //计算当前日期为星期几
{
    int week = 0;
    int century = year / 100;
    year = year % 100;
    week = year + year / 4 + century / 4 - 2 * century + (26 * (month + 1)) / 10 + day - 1;
    week = week % 7;
    return week;
}
//以下一直当前日期计算X天后的日期不包括当天
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
    int x, y, m, d;
    scanf("%d%d%d%d", &x, &y, &m, &d); //要计算的天数，和当前年月日
    int id = getId(y, m, d);
    id += x;
    auto ret = date(id);                          //这个vector的用法好帅！
    printf("%d %d %d\n", ret[0], ret[1], ret[2]); //输出到达点的年月日
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
}