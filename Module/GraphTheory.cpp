#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;
/*
最近公共祖先
单次查询的时间复杂度为log n
*/
struct LCA
{
    int n, m, s;
    int head[maxn], tot, lg[maxn], fa[maxn][22], depth[maxn];
    struct Edge
    {
        int fr, to, w, nxt;
    } edge[maxn];
    void init()
    {
        tot = 0;
        fill(head, head + 1 + n, -1);
    }
    void addEdge(int fr, int to, int w)
    {
        edge[tot] = (Edge){fr, to, w, head[fr]};
        head[fr] = tot++;
    }
    void dfs(int now, int father)
    { //dfs建树
        fa[now][0] = father, depth[now] = depth[father] + 1;
        for (int i = 1; (1 << i) <= depth[now]; i++)
            fa[now][i] = fa[fa[now][i - 1]][i - 1];
        for (int i = head[now]; ~i; i = edge[i].nxt)
            if (edge[i].to != father)
                dfs(edge[i].to, now);
    }
    void pre()
    {
        for (int i = 1; i <= n; i++)
            lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
        depth[0] = 0;
        dfs(s, 0);
    }
    int getans(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);
        while (depth[u] > depth[v])
            u = fa[u][lg[depth[u] - depth[v]] - 1];
        if (u == v)
            return u;
        for (int k = lg[depth[u]] - 1; k >= 0; k--)
            if (fa[u][k] != fa[v][k])
                u = fa[u][k], v = fa[v][k];
        return fa[u][0];
    }
    void getLCA()
    {
        scanf("%d %d %d", &n, &m, &s); //点的数量，询问数量、源点数量
        init();
        for (int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v, 0);
            addEdge(v, u, 0);
        }
        pre();
        while (m--)
        {
            int u, v;
            scanf("%d %d", &u, &v); //查询两个点的最近公共祖先
            printf("%d\n", getans(u, v));
        }
    }
};
/*
边权为点权的异或，异或最小生成树
时间复杂度为 mlogn
*/
struct XOR_MST
{
    int n, a[maxn];
    int trie[maxn * 30][2], tot = 0;
    ll ans = 0;
    void Insert(int x)
    {
        int root = 0;
        for (int i = 29; i >= 0; i--)
        {
            int now = (x >> i) & 1;
            if (!trie[root][now])
                trie[root][now] = ++tot;
            root = trie[root][now];
        }
    }
    int Search(int x)
    {
        int tans = 0, root = 0;
        for (int i = 29; i >= 0; i--)
        {
            int now = (x >> i) & 1;
            if (trie[root][now])
                root = trie[root][now];
            else
                root = trie[root][now ^ 1], tans |= (1 << i);
        }
        return tans;
    }
    void dfs(int l, int r, int depth)
    {
        if (depth == -1 || l >= r)
            return;
        int mid = l - 1;
        while (mid < r && ((a[mid + 1] >> depth) & 1) == 0)
            mid++;
        dfs(l, mid, depth - 1);
        dfs(mid + 1, r, depth - 1);
        if (mid == l - 1 || mid == r)
            return;
        for (int i = l; i <= mid; i++)
            Insert(a[i]);
        int tmp = INT32_MAX;
        for (int i = mid + 1; i <= r; i++)
            tmp = min(tmp, Search(a[i]));
        ans += 1ll * tmp;
        for (int i = 0; i <= tot; i++)
            trie[i][0] = trie[i][1] = 0;
        tot = 0;
    }
    int main()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        sort(a + 1, a + 1 + n);
        dfs(1, n, 29);
        printf("%lld", ans);
        return 0;
    }
};
/*
最大生成树 取 LCA路径上的最小值 Kruscal
*/
struct MAST_LCA_route_minnum
{
    int n, m, tot = 0;
    int head[maxn], fa[maxn], depth[maxn];
    int sfa[maxn][15], mn[maxn][15];
    struct EEdge //最大生成树 边的排列
    {
        int fr, to, w;
        bool operator<(const EEdge x) const
        {
            return w > x.w;
        }
    } sedge[maxn];
    struct Edge //LCA边
    {
        int fr, to, w, nxt;
    } edge[maxn];
    void addEdge(int u, int v, int w)
    {
        edge[tot] = (Edge){u, v, w, head[u]};
        head[u] = tot++;
    }
    int fdfa(int x) //并查集
    {
        return fa[x] == x ? x : fa[x] = fdfa(fa[x]);
    }
    void dfs(int now, int pa)
    {
        for (int i = head[now]; ~i; i = edge[i].nxt)
        {
            int to = edge[i].to, w = edge[i].w;
            if (to == pa)
                continue;
            depth[to] = depth[now] + 1;
            sfa[to][0] = now;
            mn[to][0] = w;
            dfs(to, now);
        }
    }
    int lca(int u, int v)
    {
        if (depth[u] == -1 || depth[v] == -1)
            return -1;
        if (depth[u] > depth[v])
            swap(u, v);
        for (int i = 0; i < 15; i++)
            if ((depth[v] - depth[u]) & (1 << i))
                v = sfa[v][i];
        if (u == v)
            return u;
        for (int i = 14; i >= 0; i--)
            if (sfa[u][i] != sfa[v][i])
                u = sfa[u][i], v = sfa[v][i];
        return sfa[u][0];
    }
    int ask(int u, int st)
    {
        int ret = 0x7fffffff;
        for (int i = 0; i < 15; i++)
            if (st & (1 << i))
                ret = min(ret, mn[u][i]), u = sfa[u][i];
        return ret;
    }
    int main()
    {
        scanf("%d %d", &n, &m);
        fill(head, head + 1 + n, -1);
        fill(depth, depth + 1 + n, -1);
        for (int i = 1; i <= n; i++)
            fa[i] = i;
        for (int i = 1; i <= m; i++)
            scanf("%d %d %d", &sedge[i].fr, &sedge[i].to, &sedge[i].w);
        sort(sedge + 1, sedge + 1 + m);
        int k = 0;
        for (int i = 1; i <= m; i++)
        {
            if (k == n - 1)
                break;
            if (fdfa(sedge[i].fr) != fdfa(sedge[i].to))
            {
                int u = sedge[i].fr, v = sedge[i].to, w = sedge[i].w;
                addEdge(u, v, w);
                addEdge(v, u, w);
                fa[fdfa(v)] = fdfa(u);
                k++;
            }
        } //循环建立最大生成树
        depth[1] = 1;
        dfs(1, 0);
        // printf("YES\n");
        for (int i = 1; i < 15; i++)
            for (int j = 1; j <= n; j++)
            {
                sfa[j][i] = sfa[sfa[j][i - 1]][i - 1];                  //记录路径父亲节点
                mn[j][i] = min(mn[j][i - 1], mn[sfa[j][i - 1]][i - 1]); //记录路径边权最小值
            }
        int q;
        scanf("%d", &q);
        while (q--)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            int ffa = lca(u, v); //找不到LCA返回-1
            if (ffa != -1)       //两边的路径上最小值，再取最小值
                printf("%d\n", min(ask(u, depth[u] - depth[ffa]), ask(v, depth[v] - depth[ffa])));
            else
                printf("-1\n");
        }
        return 0;
    }
};
/*
最短路
迪杰斯特拉 dijkstra
时间复杂度：不使用堆优化O（n^2)     使用堆优化O((m+n)log n)
堆优化适用稀疏图
*/
struct shortest_path
{
    #define ll long long
    #define pii pair<ll,int>
    int tot, head[maxn];
    ll dis[maxn];
    bool vis[maxn];
    int n,m,s;
    struct Edge{
        int to;
        ll w;
        int nxt;
    }edge[maxn<<2];
    void init()
    {
        tot = 0;
        fill(head, head + 1 + n, -1);
        fill(dis, dis + 1 + n, INT32_MAX);
        fill(vis, vis + 1 + n, 0);
    }
    void addEdge(int fr, int to, ll w)
    {
        edge[tot].to = to,edge[tot].w = w,edge[tot].nxt = head[fr];
        head[fr] = tot++;
    }
    priority_queue<pii,vector<pii>,greater<pii>> Q;
    void dij(){
        while(!Q.empty())
            Q.pop();
        dis[s]=0;
        Q.push(make_pair(0,s));
        while(!Q.empty()){
            pii now = Q.top();
            Q.pop();
            if(vis[now.second])
                continue; 
            int node = now.second;
            vis[node]=1;
            for(int i = head[node];~i;i=edge[i].nxt)
            if(dis[edge[i].to] > dis[node] + edge[i].w){
                dis[edge[i].to] = dis[node] + edge[i].w;
                if(!vis[edge[i].to])
                    Q.push(make_pair(dis[edge[i].to],edge[i].to));
            }
        }
    }
    int main(){
        scanf("%d %d %d",&n,&m,&s);
        init();
        for(int i=1;i<=m;i++)
        {
            int u,v;
            ll w;
            scanf("%d %d %lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        dij();
        for(int i=1;i<=n;i++)
            printf("%lld ",dis[i]);
    return 0;
    }
};
/*
次短路径
同样dij
本例是每条路径可重复使用路径
*/
struct the_Second_Short_Path{
    int n, m, s, head[maxn], vis[maxn], tot;
    int dist1[maxn], dist2[maxn];
    struct Edge {
        int to, w, nxt;
    }edge[maxn];
    int x, y,cur;
    void add(int fr, int to, int w)
    {
        edge[tot].to = to;
        edge[tot].w = w;
        edge[tot].nxt = head[fr];
        head[fr] = tot++;
    }
    ll dij()
    {
        for (int i = 0; i < n; i++)
            dist1[i] = dist2[i] = 1e9+7;
        queue <int> q;
        q.push(0);
        dist1[0] = 0;
        vis[0] = 1;
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            vis[cur] = 0;
            for (int i = head[cur]; ~i; i = edge[i].nxt)
            {
                int to = edge[i].to;//以下三个if是关键，
                if (dist1[to] > dist1[cur] + edge[i].w)//最短更新，次短变最短
                {
                    dist2[to] = dist1[to];
                    dist1[to] = dist1[cur] + edge[i].w;
                    if (!vis[to]) vis[to] = 1, q.push(to);
                }
                if (dist2[to] > dist2[cur] + edge[i].w)//次短由上一个点的次短更新，
                {
                    dist2[to] = dist2[cur] + edge[i].w;
                    if (!vis[to]) vis[to] = 1, q.push(to);
                }
                if (dist1[to] < dist1[cur] + edge[i].w && dist2[to] > dist1[cur] + edge[i].w)
                {
                    dist2[to] = dist1[cur] + edge[i].w;
                    if (!vis[to]) vis[to] = 1, q.push(to);
                }
            }
        }
        return dist2[n-1];
    }
    int main()
    {
        scanf("%d %d", &n, &m);
        fill(head,head+1+n,-1);
        for (int i = 0; i < m; i++)
        {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            add(a, b, c), add(b, a, c);
        }
        printf("%lld", dij());
        return 0;
    }
};
/*
Prufer序列
Prufer序列能够将无根树变成一个唯一的序列
能够将无根树化成唯一的一个序列，又能从这个唯一序列中化出无根树
*/
struct Prufer
{ //洛谷P6086
    int n, m;
    int fa[maxn], d[maxn], p[maxn]; //给定父亲序列，或者给定prufer序列
    ll ans = 0;                     //记录度数，答案
    int main()
    {
        scanf("%d %d", &n, &m);
        if (m == 1) //树转Prufer序列
        {
            for (int i = 1; i < n; i++)
                scanf("%d", &fa[i]), ++d[fa[i]]; //对父亲节点度数+1
            for (int i = 1, j = 1; i <= n - 2; i++, j++)
            {
                while (d[j]) //查询第一个位置度数为0的点
                    ++j;
                p[i] = fa[j];                                //将这个度数为0的点添加进prufer序列
                while (i <= n - 2 && !--d[p[i]] && p[i] < j) //如果起到了连锁反应即一直更新
                    p[i + 1] = fa[p[i]], ++i;
            }
            for (int i = 1; i <= n - 2; i++)
                ans ^= 1ll * i * p[i]; //求prufer序列的i*a[i]异或和
        }
        else //Prufer序列转树
        {
            for (int i = 1; i <= n - 2; i++)
                scanf("%d", &p[i]), ++d[p[i]];
            p[n - 1] = n;
            for (int i = 1, j = 1; i < n; i++, j++)
            {
                while (d[j]) //找到第一个度数为0的点
                    ++j;
                fa[j] = p[i]; //反向设定
                while (i < n && !--d[p[i]] && p[i] < j)
                    fa[p[i]] = p[i + 1], ++i;
            }
            for (int i = 1; i < n; i++)
                ans ^= 1ll * i * fa[i]; //求fa数组的i*fa[i] 异或和
        }
        printf("%lld", ans);
        return 0;
    }
};
/*
LCA+差分数组
计算树上节点的最大值——树上 点的差分
例题：洛谷P3128  [USACO15DEC]Max Flow P
在树上查找所有边里的最大流量，此题每条线路流量为1
时间复杂度为 O(n) 修改和查询都是O(n)
*/
struct DifferentialArray //On Node
{
    int n, k, tot;
    int head[maxn], depth[maxn], lg[maxn], fa[maxn][32];
    int chafen[maxn], ans;
    struct Edge
    {
        int fr, to, nxt;
    } edge[maxn];
    void init()
    {
        tot = 0, ans = -1;
        fill(head, head + 1 + n, -1);
    }
    void addEdge(int fr, int to)
    {
        edge[tot] = (Edge){fr, to, head[fr]};
        head[fr] = tot++;
    }
    void dfs(int now, int father)
    { //dfs建树
        fa[now][0] = father, depth[now] = depth[father] + 1;
        for (int i = 1; (1 << i) <= depth[now]; i++)
            fa[now][i] = fa[fa[now][i - 1]][i - 1];
        for (int i = head[now]; ~i; i = edge[i].nxt)
            if (edge[i].to != father)
                dfs(edge[i].to, now);
    }
    void pre()
    {
        for (int i = 1; i <= n; i++)
            lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
        depth[0] = 0;
        dfs(1, 0);
    }
    int getLCA(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);
        while (depth[u] > depth[v])
            u = fa[u][lg[depth[u] - depth[v]] - 1];
        if (u == v)
            return u;
        for (int k = lg[depth[u]] - 1; k >= 0; k--)
            if (fa[u][k] != fa[v][k])
                u = fa[u][k], v = fa[v][k];
        return fa[u][0];
    }
    void sum(int now)
    {
        for (int i = head[now]; ~i; i = edge[i].nxt)
            if (edge[i].to != fa[now][0])
            {
                sum(edge[i].to);
                chafen[now] += chafen[edge[i].to];
            }
        ans = max(ans, chafen[now]);
    }
    int main()
    {
        scanf("%d %d", &n, &k);
        init();
        for (int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        pre();
        for (int i = 1; i <= k; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            int lca = getLCA(u, v); //使用LCA求得最近公共祖先
            chafen[u]++, chafen[lca]--;
            chafen[v]++, chafen[fa[lca][0]]--;
        }
        sum(1);
        printf("%d", ans);
        return 0;
    }
};
/*
树链剖分    
洛谷P3384轻重链剖分
时间复杂度为O(n)建立，O(logn)修改单点权值，统计路径信息为O(logn * logn)
所以总的来说时间复杂度为O(nlogn*logn)
*/
struct Tree_chain_subdivision
{
    struct Edge{
        int to,nxt;
    }edge[maxn<<1];
    struct node{
        int l, r, ls, rs;
        ll sum, lazy;
    }tree[maxn<<2];
    ll mod;
    int n, m, r, rt,  v[maxn], head[maxn];
    int cnt, f[maxn], d[maxn], son[maxn], size[maxn], top[maxn], id[maxn], rk[maxn];
    //f记录每个节点的父亲，d记录深度，son记录该点的重儿子，size记录以该节点为根的子树的节点总数
    //top记录每个点所在重链的顶点，id记录在每个点的dfs序，rk记录dfs序对应的节点编号
    int opt, x, y, z;
    void add(int fr,int to)
    {
        edge[cnt] = (Edge){ to, head[fr]};
        head[fr]=cnt++;
    }
    void dfs1(int x)
    {
        // printf("%d\n", x);
        size[x]=1,d[x]=d[f[x]]+1;
        for(int v,i=head[x];~i;i=edge[i].nxt)
            if((v=edge[i].to)!=f[x])
            {
                f[v]=x,dfs1(v),size[x]+=size[v];
                if(size[son[x]]<size[v])
                    son[x]=v;
            }
    }
    void dfs2(int x,int tp)
    {
        top[x]=tp,id[x]=++cnt,rk[cnt]=x;
        if(son[x])
            dfs2(son[x],tp);
        for(int v,i=head[x];~i;i=edge[i].nxt)
            if((v=edge[i].to)!=f[x]&&v!=son[x])
                dfs2(v,v);
    }
    inline void pushup(int x)
    {
        tree[x].sum=(tree[tree[x].ls].sum+tree[tree[x].rs].sum)%mod;
    }
    void build(int l,int r,int x)
    {
        if(l==r)
        {
            tree[x].sum=v[rk[l]],tree[x].l=tree[x].r=l;
            return;
        }
        int mid=l+r>>1;
        tree[x].ls=cnt++,tree[x].rs=cnt++;
        build(l,mid,tree[x].ls),build(mid+1,r,tree[x].rs);
        tree[x].l=tree[tree[x].ls].l,tree[x].r=tree[tree[x].rs].r;
        pushup(x);
    }
    inline int len(int x)
    {
        return tree[x].r-tree[x].l+1;
    }
    inline void pushdown(int x)
    {
        if(tree[x].lazy)
        {
            int ls=tree[x].ls,rs=tree[x].rs,lz=tree[x].lazy;
            (tree[ls].lazy+=lz)%=mod,(tree[rs].lazy+=lz)%=mod;
            (tree[ls].sum+=lz*len(ls))%=mod,(tree[rs].sum+=lz*len(rs))%=mod;
            tree[x].lazy=0;
        }
    }
    void update(int l,int r,int c,int x)
    {
        if(tree[x].l>=l&&tree[x].r<=r)
        {
            (tree[x].lazy+=c)%=mod,(tree[x].sum+=len(x)*c)%=mod;
            return;
        }
        pushdown(x);
        int mid=(tree[x].l+tree[x].r)>>1;
        if(mid>=l)
            update(l,r,c,tree[x].ls);
        if(mid<r)
            update(l,r,c,tree[x].rs);
        pushup(x);
    }
    int query(int l,int r,int x)
    {
        if(tree[x].l>=l&&tree[x].r<=r)
            return tree[x].sum;
        pushdown(x);
        int mid=tree[x].l+tree[x].r>>1,tot=0;
        if(mid>=l)
            tot+=query(l,r,tree[x].ls);
        if(mid<r)
            tot+=query(l,r,tree[x].rs);
        return tot%mod;
    }
    inline int sum(int x,int y)
    {
        int ret=0;
        while(top[x]!=top[y])
        {
            if(d[top[x]]<d[top[y]])
                swap(x,y);
            (ret+=query(id[top[x]],id[x],rt))%=mod;
            x=f[top[x]];
        }
        if(id[x]>id[y])
            swap(x,y);
        return (ret+query(id[x],id[y],rt))%mod;
    }
    inline void updates(int x,int y,int c)//注意updates和update函数
    {
        while(top[x]!=top[y])
        {
            if(d[top[x]]<d[top[y]])
                swap(x,y);
            update(id[top[x]],id[x],c,rt);
            x=f[top[x]];
        }
        if(id[x]>id[y])
            swap(x,y);
        update(id[x],id[y],c,rt);
    }
    signed main()
    {
        scanf("%d %d %d %lld",&n,&m,&r,&mod);
        for(int i=1;i<=n;i++)
            scanf("%d",&v[i]);
        fill(head,head+1+n,-1);
        for(int x,y,i=1;i<n;i++)
        {
            scanf("%d %d",&x,&y);
            add(x,y),add(y,x);
        }
        cnt=0,dfs1(r),dfs2(r,r);
        cnt=0,build(1,n,rt=cnt++);
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&opt);
            if(opt==1)
            {
                scanf("%d %d %d",&x,&y,&z);
                updates(x,y,z);
            }
            else if(opt==2)
            {
                scanf("%d %d",&x,&y);
                printf("%lld\n",sum(x,y)%mod);
            }
            else if(opt==3)
            {
                scanf("%d %d",&x,&y);
                update(id[x],id[x]+size[x]-1,y,rt);
            }
            else
            {
                scanf("%d",&x);
                printf("%lld\n",query(id[x],id[x]+size[x]-1,rt)%mod);
            }
        }
        return 0;
    }
};
/*
动态规划求树的重心
时间复杂度为O(n)
确定哪一个点的所有子树中的最大子树最小即可
以POJ
*/
struct Tree_Center_gravity{
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
};
/*
点分治 经典框架就是求一棵树上距离为k的点对有多少个
本例以洛谷 点分治模板题为例 m个询问，问距离为k的点对有多少个,离线
时间复杂度为 O(nlogn)
*/
struct Point_Division{
    int n,m;
    int head[maxn],tot=0;
    int sz[maxn],mp[maxn],sum,rt;
    bool vis[maxn];
    int dis[maxn],tmp[maxn],cnt=0;
    int jd[maxn];
    int k[maxn],ans[maxn];
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
            for(int o =1;o<=m;o++){
                for (int j = 0; j < cnt; j++)
                        if (k[o] >= tmp[j] && tmp[j] <1*1e7+1) //防爆数组
                            ans[o] += jd[k[o]-tmp[j]];//jd数组是一个桶数组，jd[i]为路径i的数量
            }
            for (int j = 0; j < cnt; j++)
            {
                if(tmp[j]<1e7+1){//为防止爆数组，需要特判一下
                    que.push(tmp[j]);
                    jd[tmp[j]]++;//每找一个子树就压进去一批
                }
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
        scanf("%d %d",&n,&m);
        fill(head,head+1+n,-1);
        for(int i=1;i<n;i++)
        {
            int u,v,w;
            scanf("%d %d %d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        for(int i=1;i<=m;i++)
            scanf("%d",&k[i]);
        mp[0] = sum = n;
        getrt(1, 0);//找整树的重心
        getrt(rt, 0);//为啥是两遍？因为我们需要让siz数组正确（换根后siz数组就不正确了
        divide(rt);
        for(int i=1;i<=m;i++)
        if(ans[i]>0)
            printf("AYE\n");
        else
            printf("NAY\n");
        return 0;
    }
};