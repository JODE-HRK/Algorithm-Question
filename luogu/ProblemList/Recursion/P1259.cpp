#include <bits/stdc++.h>
using namespace std;
int n;
void print1(int s, string k)
{
    for (int i = 0; i < s; i++)
        cout << k;
}
void dfs(int sum, int cnt)
{
    if (sum == 3)
    {
        printf("ooo*o**--*");
        print1(cnt - 1, "o*");
        cout << endl;
        printf("o--*o**oo*");
        print1(cnt - 1, "o*");
        cout << endl;
        printf("o*o*o*--o*");
        print1(cnt - 1, "o*");
        cout << endl;
        printf("--o*o*o*o*");
        print1(cnt - 1, "o*");
        cout << endl;
        return;
    }
    print1(sum, "o");
    print1(sum, "*");
    cout << "--";
    print1(cnt, "o*");
    cout << endl;
    print1(sum - 1, "o");
    cout << "--";
    print1(sum - 1, "*");
    print1(cnt + 1, "o*");
    cout << endl;
    dfs(sum - 1, cnt + 1);
}
int main()
{
    scanf("%d", &n);
    dfs(n, 0);
    return 0;
}