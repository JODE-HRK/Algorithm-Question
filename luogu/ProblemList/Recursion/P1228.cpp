#include <bits/stdc++.h>
using namespace std;
long long k, x, y;
void dfs(long long xx, long long yy, long long a, long long b, long long l)
{
    if (l == 1)
        return;
    if (xx < a + l / 2 && yy < b + l / 2) //在左下
    {
        cout << a + l / 2 << ' ' << b + l / 2 << ' ' << 1 << endl;
        dfs(xx, yy, a, b, l / 2);                               //左下
        dfs(a + l / 2 - 1, b + l / 2, a, b + l / 2, l / 2);     //左上
        dfs(a + l / 2, b + l / 2 - 1, a + l / 2, b, l / 2);     //右下
        dfs(a + l / 2, b + l / 2, a + l / 2, b + l / 2, l / 2); //右上
    }
    else if (xx < a + l / 2 && yy >= b + l / 2) //在左上
    {
        cout << a + l / 2 << ' ' << b + l / 2 - 1 << ' ' << 2 << endl;
        dfs(a + l / 2 - 1, b + l / 2 - 1, a, b, l / 2);         //左下
        dfs(xx, yy, a, b + l / 2, l / 2);                       //左上
        dfs(a + l / 2, b + l / 2 - 1, a + l / 2, b, l / 2);     //右下
        dfs(a + l / 2, b + l / 2, a + l / 2, b + l / 2, l / 2); //右上
    }
    else if (xx >= a + l / 2 && yy >= b + l / 2) //在右上
    {
        cout << a + l / 2 - 1 << ' ' << b + l / 2 - 1 << ' ' << 4 << endl;
        dfs(a + l / 2 - 1, b + l / 2 - 1, a, b, l / 2);     //左下
        dfs(a + l / 2 - 1, b + l / 2, a, b + l / 2, l / 2); //左上
        dfs(a + l / 2, b + l / 2 - 1, a + l / 2, b, l / 2); //右下
        dfs(xx, yy, a + l / 2, b + l / 2, l / 2);           //右上
    }
    else
    { //在右下
        cout << a + l / 2 - 1 << ' ' << b + l / 2 << ' ' << 3 << endl;
        dfs(a + l / 2 - 1, b + l / 2 - 1, a, b, l / 2);         //左下
        dfs(a + l / 2 - 1, b + l / 2, a, b + l / 2, l / 2);     //左上
        dfs(xx, yy, a + l / 2, b, l / 2);                       //右下
        dfs(a + l / 2, b + l / 2, a + l / 2, b + l / 2, l / 2); //右上
    }
}
long long poww(long long k)
{
    long sum = 1;
    while (k--)
    {
        sum *= 2;
    }
    return sum;
}
int main()
{
    scanf("%lld %lld %lld", &k, &x, &y);
    long long t = poww(k);
    //cout<<t<<endl;
    dfs(x, y, 1, 1, t);
    return 0;
}