#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
struct L
{
    int r;
    string name;
} a[21];
bool cmp(L x, L y)
{
    return x.r < y.r;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        char s[1001];
        cin >> s;
        if (s[0] > '9' || s[0] < '0')
            a[i].name = s;
        else
            a[i].r = atoi(s) / 2;
        cin >> s;
        if (s[0] > '9' || s[0] < '0')
            a[i].name = s;
        else
            a[i].r = atoi(s);
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
        cout << a[i].name << endl;
    return 0;
}