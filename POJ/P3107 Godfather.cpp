#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iomanip>
// #include <queue>
using namespace std;
const int maxn = 2e5+7;
int n;
int head[maxn],tot=0;
int sum[maxn],maxsubtree[maxn];
int maxsub = 0x7fffffff;
// priority_queue <int> Q;
struct Edge{
    int to,nxt;
}edge[maxn];
void init(){
    for(int i=1;i<=n;i++)
        head[i]=-1;
}
void dfs(int now,int fa){
    sum[now] = 1;
    maxsubtree[now] = -1;
    for(int i=head[now];~i;i = edge[i].nxt)
    if(edge[i].to != fa)
    {
        dfs(edge[i].to,now);
        sum[now] += sum[edge[i].to];
        maxsubtree[now] = max(maxsubtree[now],sum[edge[i].to]);
    }
    maxsubtree[now] = max(maxsubtree[now],n-sum[now]);
    if(maxsubtree[now] <= maxsub)
        maxsub = maxsubtree[now];
}
inline int read(){
    char c = getchar();int x = 0,fh = 0;
    while(c < '0' || c > '9'){fh |= c == '-';c = getchar();}
    while(c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}
    return fh?-x:x;
}
void addEdge(int fr,int to){
    edge[tot] = (Edge){to,head[fr]};
    head[fr] = tot++;
}
int main(){
    n = read();
    init();
    for(int i=1;i<n;i++){
        int u,v;    
        u = read(),v = read();
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,0);
    // for(int i=1;i<=n;i++){
    //     printf("i:%d sum:%d maxsubtree:%d\n",i,sum[i],maxsubtree[i]);
    // }
    // sort(Ans.begin(),Ans.end());
    for(int i=1;i<=n;i++)
    if(maxsubtree[i] == maxsub)
        printf("%d ",i);
return 0;
}