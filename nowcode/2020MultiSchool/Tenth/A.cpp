/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-14 20:33:14
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-14 20:58:52
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int p, t;
bool vis[maxn];
vector<int> ans;
void init()
{
    ans.clear();
    fill(vis, vis + 1 + p, 0);
}
void dfs(int now)
{
    vis[now] = 1;
    ans.push_back(now);
    int nowx = now * 2 % p, nowy = now * 3 % p;
    if (nowx && !vis[nowx])
        dfs(nowx);
    else if (nowy && !vis[nowy])
        dfs(nowy);
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &p);
        init();
        // ans.push_back(1);
        dfs(1);
        // for (int i = 0; i < ans.size(); i++)
        //     printf("%d ", ans[i]);
        // cout << endl;
        if (ans.size() != p - 1)
            printf("-1\n");
        else
        {
            for (int i = 0; i < ans.size(); i++)
                printf("%d ", ans[i]);
            cout << endl;
        }
    }
    return 0;
}