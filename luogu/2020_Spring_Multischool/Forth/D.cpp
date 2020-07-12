#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int n, k;
int b[maxn];
string s;
int main()
{
    scanf("%d %d", &n, &k);
    cin >> s;
    for (int i = 0; i < n; i++)
        b[i] = (s[i] - s[(i + n - 1) % n] + 10) % 10;
    int p = __gcd(n, k); //p为所成的环数
    for (int i = 0; i < p; i++)
    {
        int j = i, r = 0;
        do
        {
            r = (r + b[j]) % 10;
            j = (j + k) % n;
        } while (i != j);
        if (r)
        {
            printf("No");
            return 0;
        }
    }
    printf("Yes");
    return 0;
}