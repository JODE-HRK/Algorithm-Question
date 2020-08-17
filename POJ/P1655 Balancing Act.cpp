#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;
const int maxn = 2e5+7;
int n;
vector<int> G[maxn];
int sum[maxn],maxsubtree[maxn];
int maxsub,ansnode;
void init(){
    maxsub = 0x7fffffff;
    ansnode = 0x7fffffff;
    for(int i=1;i<=n;i++)
        G[i].clear();
}
void dfs(int now,int fa){
    sum[now] = 1;
    maxsubtree[now] = -1;
    for(int i=0;i<G[now].size();i++)
    if(G[now][i] != fa)
    {
        dfs(G[now][i],now);
        sum[now] += sum[G[now][i]];
        maxsubtree[now] = max(maxsubtree[now],sum[G[now][i]]);
    }
    maxsubtree[now] = max(maxsubtree[now],n-sum[now]);
    if(maxsubtree[now] <= maxsub)
    {
        if(maxsubtree[now] == maxsub)
            ansnode = min(ansnode,now);
        else
            ansnode = now;
        maxsub = maxsubtree[now];
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        init();
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1,0);
        printf("%d %d\n",ansnode,maxsub);
    }
return 0;
}