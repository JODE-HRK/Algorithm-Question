#include <bits/stdc++.h>
using namespace std;
int n, boundl, boundr;
bool a[3001];
int main()
{ //和杨辉三角比对一下
    scanf("%d", &n);
    a[0] = 1;
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 1; j < (1 << n) - i; j++)
            cout << ' ';//此处为前面的空格
        for (int j = i; j >= 0; j--)
            a[j] ^= a[j - 1];
        if (i % 2)
            for (int j = 0; j <= i; j += 2)
                cout << (a[j] ? "/__\\" : "    ");
        else
            for (int j = 0; j <= i; j++)
                cout << (a[j] ? "/\\" : "  ");
        cout << endl;
    }
    return 0;
}