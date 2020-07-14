/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-13 21:37:37
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-14 10:59:41
 */ 
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
int n,tot=0,sum=0;
int d[maxn],vis[maxn],num=0;
vector<int> G[maxn];
vector<int> Ans;
void dfs(int node,int fa){
    if(d[node] == 1){
        sum++;
        Ans.push_back(node);
        return;
    }
    for (int i = 0; i<G[node].size() ;i++){
        int to = G[node][i];
        if(fa != to){
            vis[to] = 1;
            dfs(to,node);
        }
    }
    return;
}
int main(){
    scanf("%d", &n);
    fill(d, d + maxn, 0);
    Ans.clear();
    for (int i = 1; i < n;i++){
        int a, b;
        scanf("%d %d",&a,&b);
        G[a].push_back(b);
        G[b].push_back(a);
        d[a]++, d[b]++;
    }
    if(n==2)
    {
        printf("1\n");
        printf("1 2\n");
        return 0;
    }
    int root = 1;
    while(d[root] == 1)
        root++;
    vis[root] = 1;
    dfs(root,0);
    // for (int i = 0;i<sum;i++)
    //     printf("%d ", Ans[i]);
    // printf("%d\n", sum);
    printf("%d\n", (sum + 1) / 2);
    for (int i = 0; (sum+1) / 2 + i<sum;i++)
        printf("%d %d\n", Ans[i], Ans[(sum+1) / 2 + i]);
    if(sum%2==1)
        printf("%d %d\n", root, Ans[sum / 2]);
    return 0;
}