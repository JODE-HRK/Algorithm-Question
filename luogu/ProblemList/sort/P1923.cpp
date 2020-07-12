#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e6 + 7;
int n, k;
int a[maxn];
int main()
{
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n);
    printf("%d", a[k + 1]);
    return 0;
}