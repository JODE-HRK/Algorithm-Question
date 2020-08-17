#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5+7;
const int mod = 998244353;
int n,k;
int sum[maxn],maxsubtree[maxn],ansnode,maxsub;
struct Node{
	int depth,col;
}node[maxn];
int pre[maxn],after[maxn];
vector<int> G[maxn];
vector<int> S[maxn];
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
void dfs2(int now,int fa,int color){
	node[now].col = color;
	node[now].depth = node[fa].depth+1;
	for(int i=0;i<G[now].size();i++)
	if(G[now][i] != fa)
		dfs2(G[now][i],now,color);
}
bool cmp(Node x,Node y){
	return x.depth<y.depth;
}
int getans(int x,int color){
	int l = 1, r = n;
	while(l<r){
		int mid = (l+r)>>1;
		if(node[mid].depth<x)
			l=mid+1;
		else if(node[mid].depth>x)
			r = mid-1;
		else{
			l = pre[mid],r = after[mid];
			break;
		}
	}
	if(l>=r)
		return 0;
	return (r-l+1) - (upper_bound(S[x].begin(),S[x].end(),r) - lower_bound(S[x].begin(),S[x].end(),l));
}
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	node[ansnode].depth = 0;
	node[ansnode].col = 0;
	for(int i=0;i<G[ansnode].size();i++)
		dfs2(G[ansnode][i],ansnode,i+1);
	sort(node+1,node+1+n,cmp);
	for(int i=1;i<=n;i++){
		S[node[i].col].push_back(i);
		if(node[i].depth!=node[i-1].depth)
			pre[i] = i;
		else pre[i] = pre[i-1];
	}
	for(int i=n;i>=1;i--){
		if(node[i].depth!=node[i+1].depth)
				pre[i] = i;
		else after[i] = after[i-1];
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	if(node[i].col){
		if(node[i].depth<k){
			ans+=getans(k-node[i].depth,node[i].col);
		}
		else if(node[i].depth == k)
			ans++;
	}	
	printf("%d",ans);
	return 0;
}