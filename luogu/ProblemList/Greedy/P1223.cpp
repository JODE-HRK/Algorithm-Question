#include <bits/stdc++.h>
using namespace std;
int n;
struct op
{
    int id, t;
} a[1001];
bool cmp(op x, op y)
{
    return x.t < y.t;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i].t), a[i].id = i;
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i].id);
    cout << endl;
    double sum = 0, tp = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += tp;
        tp += a[i].t;
    }
    printf("%.2lf", sum / n);
    return 0;
}