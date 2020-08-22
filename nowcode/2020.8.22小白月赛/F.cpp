#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<int> G[1001];
int g[1001][1001];
int r[1001];
bool vis[1001];
int sum[1001];
void dfs(int now){
    vis[now] = 1;
    if(sum[now])
        return;
    for(int i=0;i<G[now].size();i++){
        dfs(G[now][i]);
        sum[now] += (sum[G[now][i]] + 1);
    }
}
int main(){
    scanf("%d %d",&n,&m);
    fill(sum,sum+1+n,0);
    fill(vis,vis+1+n,0);
    memset(g,0,sizeof(g));
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        if(!g[x][y])
            G[y].push_back(x);
        g[x][y]=1;
        r[x]++;
    }
    for(int i=1;i<=n;i++)
    if(!vis[i] && !r[i])
    {
        dfs(i);
    }
    for(int i=1;i<=n;i++)
        printf("%d\n",sum[i]);
    return 0;
}