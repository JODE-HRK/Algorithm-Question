#include <bits/stdc++.h>
using namespace std;
int n;
priority_queue<int, vector<int>, greater<int>> Q;
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        int x;
        scanf("%d", &x);
        Q.push(x);
    }
    int ans = 0;
    while (Q.size() > 1)
    {
        int x = Q.top();
        Q.pop();
        int y = Q.top();
        Q.pop();
        ans += (x + y);
        Q.push(x + y);
    }
    printf("%d", ans);
    return 0;
}