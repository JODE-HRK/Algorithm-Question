#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
using namespace std;
int n, p = 1, q = 1, id, cnt;
stack<int> Q;
int main()
{
    // freopen(".in", "r", stdin);
    scanf("%d", &n);
    while (n--)
    {
        p = q = 1;
        scanf(" %d %d", &cnt, &id);
        while (id > 1)
        {
            if (id % 2)
                Q.push(1); //1右
            else
                Q.push(0); //0左
            id /= 2;
        }
        while (!Q.empty())
        {
            int x = Q.top();
            Q.pop();
            if (x)
                p = p + q;
            else
                q = p + q;
        }
        cout << cnt << ' ' << p << '/' << q << endl;
    }
    return 0;
}