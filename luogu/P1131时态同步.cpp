#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e5+7;
int n, k;
ll dp[maxn],times[maxn];
int head[maxn], tot, size[maxn];
struct Edge {
    int fr, to, w, nxt;
}edge[maxn<<2];
void init() {
    tot=0;
    fill(head, head+1+n, -1);
    memset(dp, 0, sizeof(dp));
}
void addEdge(int fr, int to, int w) {
    edge[tot] = (Edge){ fr, to, w, head[fr] };
    head[fr] = tot++;
}
void dfs(int now, int fa) {
    dp[now]=times[now]=0;
    ll cnt=0,sum=0;
    for(int i=head[now];~i;i=edge[i].nxt)
    if(edge[i].to!=fa)
    {
        dfs(edge[i].to, now);
        cnt++, times[now]= max(times[edge[i].to]+1ll*edge[i].w, times[now]);
        sum+=edge[i].w+times[edge[i].to];
        dp[now] += dp[edge[i].to];
    }
    dp[now]+=((cnt*times[now])-sum);
}
inline int read(){
    char c = getchar();int x = 0,fh = 0;
    while(c < '0' || c > '9'){fh |= c == '-';c = getchar();}
    while(c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}
    return fh?-x:x;
}
int main()
{
    n=read(),k=read();
    init();
    for (int i=1;i<n;i++) {
        int u, v, w;
        u = read(), v = read(), w = read();
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    dfs(k, 0);
// cout<<"yes"<<endl;
    printf("%lld", dp[k]);
    return 0;
}