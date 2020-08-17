#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 3e3+7;
int n, k;
ll dp[maxn][maxn];
int head[maxn], tot, size[maxn];
struct Edge {
    int fr, to, w, nxt;
}edge[maxn<<2];
void init() {
    tot=0;
    fill(head, head+1+n, -1);
    memset(dp, -1, sizeof(dp));
}
void addEdge(int fr, int to, int w) {
    edge[tot] = (Edge){ fr, to, w, head[fr] };
    head[fr] = tot++;
}
void dfs1(int now, int fa) {
    size[now]=1;
    for (int i=head[now];~i;i=edge[i].nxt)
        if (edge[i].to != fa) {
            dfs1(edge[i].to, now);
            size[now] += size[edge[i].to];
        }
}
void dfs2(int now, int fa) {
    dp[now][0] = dp[now][1] = 0;
    for (int i=head[now];~i;i=edge[i].nxt)
        if (edge[i].to!=fa)
        {
            dfs2(edge[i].to, now);
            for (int j=min(size[now], k);j>=0;j--)
                for (int l=0;l<=min(j, size[edge[i].to]);l++)
                    if (dp[now][j-l]!=-1) {
                        ll val = 1ll*l*(k-l)*edge[i].w+1ll*(size[edge[i].to]-l)*(n-k+l-size[edge[i].to]) * edge[i].w;
                        //当前子树的黑节点×子树外的黑节点×边权+当前子树的白节点×子树外的白节点×边权
                        dp[now][j] = max(dp[now][j-l]+dp[edge[i].to][l]+val, dp[now][j]);
                    }
        }
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
    dfs1(1, 1);
// cout<<"yes"<<endl;
    dfs2(1, 1);
    printf("%lld", dp[1][k]);
    return 0;
}