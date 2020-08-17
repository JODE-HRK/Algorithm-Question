#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5+7;
int n;
int happy[maxn],dp[maxn][2];
int head[maxn],tot;
struct Edge{
    int fr, to, nxt;
}edge[maxn];
void init(){
    tot=0;
    fill(head, head+1+n, -1);
}
void addEdge(int fr,int to){
    edge[tot] = (Edge){ fr, to, head[fr] };
    head[fr] = tot++;
}
void dfs(int now,int fa){
    // printf("%d\n", now);
    dp[now][0] = 0;
    dp[now][1] = happy[now];
    for(int i=head[now];~i;i = edge[i].nxt)
    if(edge[i].to != fa)
    { 
        dfs(edge[i].to, now);
        dp[now][1]+=dp[edge[i].to][0];
        dp[now][0]+=max(dp[edge[i].to][0], dp[edge[i].to][1]);
    }
}
int main()
{
    scanf("%d", &n);
    init();
    for (int i=1;i<=n;i++)
        scanf("%d", &happy[i]);
    for(int i=1;i<n;i++){ 
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    printf("%d", max(dp[1][0], dp[1][1]));
    return 0;
}