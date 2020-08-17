#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
using namespace std;
const int maxn = 2e5+7;
const int mod = 1e9+7;
int n,m,s,t;
int head[maxn],tot=0;
int dis[maxn];
bool vis[maxn];
struct Edge{
    int to;
    int w;
    int nxt;
}edge[maxn];
void init(){
    for(int i=1;i<=n;i++)
        head[i]=-1,dis[i] = 2e9+1,vis[i]=0;
}
void addEdge(int fr,int to,int w){
    edge[tot] = (Edge){to,(int)log2((double)w+0.000001),head[fr]};
    head[fr] = tot++;
}
ll poww(ll base, ll power) //此处的power是 mod-2
{
    ll tans = 1;
    while (power)
    {
        if (power & 1)
            tans = tans * base % (1ll * mod);
        power >>= 1;
        base = (base * base) % (1ll * mod);
    }
    return tans;
}
priority_queue <pii,vector<pii>,greater<pii>> Q;.//这才是小根堆啊啊啊
void dij(){
    // printf("YES\n");
    dis[s]=0;
    Q.push((pii){dis[s],s});
    while(!Q.empty()){
        pii now = Q.top();
        Q.pop();
        int node = now.second;
        // ll d = now.first;
        if(vis[node])
            continue;
        // printf("%d\n",node);
        vis[node] = 1;
        for(int i=head[node];~i;i=edge[i].nxt){
            if(!vis[edge[i].to] && dis[edge[i].to] > dis[node] + edge[i].w)
            {
                // printf("%d ",edge[i].to);
                dis[edge[i].to] = dis[node] + edge[i].w;
                Q.push((pii){dis[edge[i].to],edge[i].to});
            }
        }
        // cout<<endl;
    }
}
int main(){
    // printf("%d\n",pow(2,2));
    while(scanf("%d %d %d %d",&n,&m,&s,&t)!=EOF)
    {    
        init();
        for(int i=1;i<=m;i++){
            int u,v;    
            ll w;
            scanf("%d %d %lld",&u,&v,&w);
            addEdge(u,v,w);
        }
        // printf("YES\n");
        dij();
        // printf("YES\n");
        if(dis[t] == 2e9+1)
        {
            printf("-1");
            return 0;
        }   
        // for(int i=1;i<=n;i++){
        //     printf("%lld %d\n",path[i].first,path[i].second);
        // }
        // printf("%d\n",dis[t]);
        printf("%lld",poww(2,dis[t]));
    }
return 0;
}