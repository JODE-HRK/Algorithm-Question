//n个人站成一圈，数m的人出圈，最后一个人胜利
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m, i, s = 0;
    cin >> n >> m;
    for (i = 2; i <= n; i++)
    {
        s = (s + m) % i;
    }
    printf("\nThe winner is %d\n", s + 1);
    return 0;
}