#include <iostream>
#include <algorithm>
using namespace std;
int n;
double sm[10001];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        scanf("%lf", &sm[i]);
    }
    sort(sm + 1, sm + 1 + n);
    double ans = 0;
    for (int i = n; i > 0; i--)
        ans += sm[i] * (n - i + 1);
    printf("%.4lf", ans);
    return 0;
}