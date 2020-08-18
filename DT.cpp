#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5+7;
const int mod = 998244353;
int n,k;
int sum[maxn],maxsubtree[maxn],ansnode,maxsub;
int a[maxn],dis[maxn],vis[maxn],ans[maxn],S;
int hdd;
struct Edge{
	int to,w;
};
vector<Edge> G[maxn];
void dfs(int now,int fa){
	sum[now] = 1;
	maxsubtree[now] = -1;
	for(int i=0;i<G[now].size();i++)
	if(G[now][i].to != fa)
	{
		dfs(G[now][i].to,now);
		sum[now] += sum[G[now][i].to];
		maxsubtree[now] = max(maxsubtree[now],sum[G[now][i].to]);
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
void getdis(int x,int len,int fa){
	dis[++hdd] = a[x];
	for(int i=0;i<G[x].size();i++)
	if(G[x][i].to!=fa){
		a[G[x][i].to] = len + G[x][i].w;
		getdis(G[x][i].to,a[G[x][i].to],x);
	}
}
void solve(int s,int len,int w){
	hdd =0 ;
	a[s] = len;
	getdis(s,len,0);
	for(int i=1;i<=hdd;i++)
		for(int j=1;j<=hdd;j++)
		if(i!=j)
		{
			ans[dis[i]+dis[j]] += w;
		}
}
void dfs2(int now,int fa,int color){
	solve(now,0,1);
	for(int i=0;i<G[now].size();i++)
	if(G[now][i].to != fa){
		solve(G[now][i].to,G[now][i].w,-1);
		S = sum[now];
		ansnode =0 ;
		
	}
}
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		G[u].push_back((Edge){v,w});
		G[v].push_back((Edge){u,w});
	}
	maxsub = 0x7fffffff;
	dfs(1,0);
	node[ansnode].dis = 0;
	node[ansnode].col = 0;
	// printf("%d\n",ansnode);
	dfs2(ansnode,0);
	
	return 0;
}