#include <bits/stdc++.h>
using namespace std;
struct Per
{
    string name;
    int year, month, day, id;
} a[100001];
int n;
bool cmp(Per x, Per y)
{
    if (x.year == y.year)
    {
        if (x.month == y.month)
        {
            if (x.day == y.day)
                return x.id > y.id;
            return x.day < y.day;
        }
        return x.month < y.month;
    }
    return x.year < y.year;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].name;
        scanf("%d %d %d", &a[i].year, &a[i].month, &a[i].day);
        a[i].id = i;
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
        cout << a[i].name << endl;
    return 0;
}