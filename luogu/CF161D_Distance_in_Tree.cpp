#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5+7;
const int mod = 998244353;
int n,m,k,ans=0;
int head[maxn],tot;
int sz[maxn],mp[maxn],sum,rt;
bool vis[maxn];
int dis[maxn],tmp[maxn],cnt=0;
int jd[maxn];
struct Edge{
	int to,w,nxt;
}edge[maxn];
void addEdge(int fr,int to,int w){
	edge[tot] = (Edge){to,w,head[fr]};
	head[fr] = tot++;
}
void getrt(int now, int f)
{
    sz[now] = 1; mp[now] = 0;//siz数组数组树子树大小
    for (int i = head[now]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (v == f || vis[v]) continue;
        getrt(v, now);
        sz[now] += sz[v];
        if (sz[v] > mp[now]) mp[now] = sz[v];//mp数组是去掉u节点后，剩余部分的最大一部分。
    }
    mp[now] = max(mp[now], sum-sz[now]);//不要忘记上子树
    if (mp[now] < mp[rt]) rt = now;//换根
}

void getdis(int u,int f){
	tmp[cnt++] = dis[u];
    for (int i = head[u]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (v == f || vis[v]) continue;
        dis[v] = dis[u] + edge[i].w;
        getdis(v, u);
    }
}

void solve(int u){
	queue<int> que;
    for (int i = head[u]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if (vis[v]) continue;
        cnt = 0;
        dis[v] = edge[i].w;
        getdis(v, u);//统计v子树的所有节点到v的距离
        for (int j = 0; j < cnt; j++)
                if (k >= tmp[j])
                    ans += jd[k-tmp[j]];//jd数组是一个桶数组，jd[i]为路径i的数量
        for (int j = 0; j < cnt; j++)
        {
            que.push(tmp[j]);
            jd[tmp[j]]++;//每找一个子树就压进去一批
        }
    }
    while(que.size())
    {
        jd[que.front()]--;
        que.pop();//以u为根的子树统计完毕，清空。
    }
}

void divide(int u)
{
    jd[0] = vis[u] = 1;//vis[i],表示u节点已被选中
    solve(u);//已u为根节点，统计路径信息
    for (int i = head[u]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(vis[v]) continue;
        mp[rt=0] = sum = sz[v];
        getrt(v, 0);//找v子树的根节点
        getrt(rt, 0);
        divide(rt);//递归划分子树
    }
}

int main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	scanf("%d %d",&n,&k);
	fill(head,head+1+n,-1);
	for(int i=1;i<n;i++)
	{
		int u,v,w;
		scanf("%d %d",&u,&v);
		addEdge(u,v,1);
		addEdge(v,u,1);
	}
	mp[0] = sum = n;
	getrt(1, 0);//找整树的重心
	// printf("YES\n");
	getrt(rt, 0);//为啥是两遍？因为我们需要让siz数组正确（换根后siz数组就不正确了）
	divide(rt);
	printf("%d",ans);
	return 0;
}