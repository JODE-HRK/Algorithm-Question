#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e5+7;
int n,m,k;
int head[maxn],tot=0;
int a[maxn];
int dp[maxn][30];
struct Edge{
    int to,nxt;
}edge[maxn];
void init(){
    tot=0;
    for(int i=1;i<=n;i++)
        head[i] = -1;
}
void addEdge(int fr,int to){
    edge[tot] = (Edge){to,head[fr]};
    head[fr] = tot++;
}
void dfs(int now,int fa){
    // printf("%d\n",now);
    dp[now][0] = a[now];
    for(int i=head[now];~i;i=edge[i].nxt)
    if(edge[i].to!=fa)
    {
        dfs(edge[i].to,now);
        for(int j=1;j<=k;j++)
            dp[now][j] += dp[edge[i].to][j-1];
    }
}
void dfs2(int now,int fa){
    for(int i=head[now];~i;i=edge[i].nxt)
    if(edge[i].to!=fa)
    {
        for(int j=k;j>1;j--)
            dp[edge[i].to][j] -= dp[edge[i].to][j-2];//注意容斥问题
        for(int j=1;j<=k;j++)
            dp[edge[i].to][j] += dp[now][j-1];
        dfs2(edge[i].to,now);
    }
}
int main(){
    scanf("%d %d",&n,&k);
    init();
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    // cout<<"YES"<<endl;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    dfs(1,0);
    dfs2(1,0);
    int ans;
    for(int i=1;i<=n;i++){
        ans=0;
        for(int j=0;j<=k;j++)
            ans += dp[i][j];
        printf("%d\n",ans);
    }
return 0;
}