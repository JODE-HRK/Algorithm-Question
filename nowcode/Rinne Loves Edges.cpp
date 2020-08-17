#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5+7;
const int mod = 998244353;
int n,m,s;
ll dp[maxn];
struct Edge
{
    int to;
    ll w;
};
vector<Edge> G[maxn];
void dfs(int now,int fa,ll last_edge){
	dp[now] = last_edge;
    ll tmp=0;
    bool p=0;
	for(int i=0;i<G[now].size();i++)
    if(G[now][i].to !=fa)
    {
        p=1;
        dfs(G[now][i].to,now,G[now][i].w);
        tmp += dp[G[now][i].to];
    }
    if(p)
        dp[now] = min(dp[now],tmp);
}
int main(){
	scanf("%d %d %d",&n,&m,&s);
	for(int i=1;i<n;i++)
	{
		int u,v;
        ll w;
		scanf("%d %d %lld",&u,&v,&w);
		G[u].push_back((Edge){v,w});
		G[v].push_back((Edge){u,w});
	}
	dfs(s,0,INT64_MAX); 
    printf("%lld",dp[s]);
	return 0;
}