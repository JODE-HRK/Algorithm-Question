#include <bits/stdc++.h>
#define pii pair<int,ll>
#define ll long long
using namespace std;
#define N 5005
#define INF 111111111               //无限大表示两边之间没有路径
struct Edge{
	int to ;
    ll w;
	bool operator <(const Edge &a)const{
		return w > a.w;
	}
};
priority_queue<Edge> Q;
vector<Edge> V[N];
int n, m;
ll dis[N], dis2[N];
void init(){
	for(int i = 0; i <= n; i++){
		V[i].clear();
		dis[i] = INF;
		dis2[i] = INF;
	}
}
ll dijkstra(){          //使用dijkstra算法
	dis[0] = 0;
	Edge p, q, r;
	p.to = 0, p.w = 0;
	Q.push(p);
	while(!Q.empty()){
		p = Q.top();
		Q.pop();
		int u = p.to;
		if(p.w > dis2[u])continue;
		for(int i = 0; i < V[u].size(); i++){
			q = V[u][i];
			int to = q.to;
            ll d = q.w + p.w;
			if(dis[to] >= d){
				dis2[to] = dis[to];
				dis[to] = d;
				r.to = to, r.w = dis[to];
				Q.push(r);
			}
			else if(dis[to] < d && dis2[to] > d){
				dis2[to] = d;
				r.to = to, r.w = d;
				Q.push(r);
			}
		}
	}
	return dis2[n-1];
}
int main(){
	int a, b;
    ll w;
	Edge p;
	while(cin>>n>>m){
		init();
		for(int i = 0; i < m; i++){
			scanf("%d %d %lld", &a, &b, &w);
			p.to = b;
			p.w = w;
			V[a].push_back(p);
			p.to = a;
			V[b].push_back(p);
		}
        printf("%lld",dijkstra());
	}
	return 0;
}