/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-08-18 23:21:16
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-08-27 12:32:45
 */
/*
倍增求k代祖先
每个点上建立主席树，求k代儿子中的第k小
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;
<<<<<<< HEAD
const int maxn = 1e6 + 7;
int n, m;
int fa[maxn][22], depth[maxn], sz[maxn], dfn[maxn], cnt = 0;
int val[maxn], head[maxn], tot = 0;
int maxdep = 0;
int root[maxn * 32], scc = 0, s[maxn * 32], lc[maxn * 32], rc[maxn * 32], id[maxn * 32], tid = 0;
vector<int> DepNode[maxn];
struct Edge
{
    int to, nxt;
} edge[maxn << 1];
bool cmp(int x, int y)
{
    if (depth[x] == depth[y])
        return dfn[x] < dfn[y];
    return depth[x] < depth[y];
}
void addEdge(int fr, int to)
{
    edge[tot] = (Edge){to, head[fr]};
    head[fr] = tot++;
}
void dfs(int now, int father)
{ //dfs建树
    sz[now] = 1;
    dfn[now] = ++cnt;
    fa[now][0] = father,
    depth[now] = depth[father] + 1;
    maxdep = max(maxdep, depth[now]);
    DepNode[depth[now]].push_back(now);
    for (int i = 1; (1 << i) <= depth[now]; i++)
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (int i = head[now]; ~i; i = edge[i].nxt)
        if (edge[i].to != father)
            dfs(edge[i].to, now), sz[now] += sz[edge[i].to];
} //dfs获取dfs序，以及每个节点下的子树的节点数量、最大深度，以及倍增求节点父亲,保存每个深度的节点
int get_k_fa(int x, int k)
{
    for (int i = 20; i >= 0; i--)
        if (k & (1 << i))
            x = fa[x][i];
    return x;
} //倍增获取k代祖先
void build(int l, int r, int &now)
{
    now = ++scc;
    s[now] = 0; //记录主席树的节点个数
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(l, mid, lc[now]), build(mid + 1, r, rc[now]); //lc、rc分别记录左右儿子
} //建立每个点的主席树
void ins(int l, int r, int las, int &pas, int x)
{
    pas = ++scc;
    lc[pas] = lc[las], rc[pas] = rc[las];
    s[pas] = s[las] + 1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        ins(l, mid, lc[las], lc[pas], x);
    else
        ins(mid + 1, r, rc[las], rc[pas], x);
}
void pre()
{
    depth[0] = 0;
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        root[i] = i;
    sort(root + 1, root + 1 + n, cmp); //以深度为第一关键字，dfs序维第二关键字排序
    build(1, n, root[0]);              //建立最初的主席树，root[0] 自然就是0
    for (int i = 1; i <= maxdep; i++)
    {
        int l = DepNode[i].size();
        for (int j = 0; j < l; j++)
        {

            int p = DepNode[i][j];
            id[p] = ++tid;                               //获得p节点在root数组里的编号
            ins(1, n, root[tid - 1], root[tid], val[p]); //将
        }
    }
}
int query(int l, int r, int x, int y, int k)
{
    if (l == r)
        return l;
    int sum = s[lc[y]] - s[lc[x]]; //左区间有多少个数
    int mid = (l + r) >> 1;
    if (sum < k)
        return query(mid + 1, r, rc[x], rc[y], k - sum);
    else
        return query(l, mid, lc[x], lc[y], k);
} //求区间第k小
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]), head[i] = -1;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    pre();
    int lastans = 0;
    for (int i = 1; i <= m; i++)
    {
        int x, k;
        scanf("%d %d", &x, &k);
        x = (x ^ lastans) % n + 1;
        if (depth[x] <= k)
        {
            puts("?");
            continue;
        }
        // printf("X:%d K:%d", x, k);
        int father = get_k_fa(x, k); //取得第k代父亲
        // printf("FA:%d\n", father);
        int lk = 0, rk = 0;
        int lm = dfn[father], rm = dfn[father] + sz[father] - 1, now = depth[father] + k;
        //lm和rm是k代祖先的子树区间
        int l = 0, r = DepNode[now].size() - 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (dfn[DepNode[now][mid]] < lm)
                l = mid + 1;
            else
                lk = DepNode[now][mid], r = mid - 1;
        }
        l = 0, r = DepNode[now].size() - 1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (dfn[DepNode[now][mid]] <= rm)
                rk = DepNode[now][mid], l = mid + 1;
            else
                r = mid - 1;
        }                            //两次二分k祖先下，所有k代儿子的dfs序区间
        if (id[rk] - id[lk] + 1 < k) //id见pre函数里面的编号
        {
            puts("?");
            continue;
        }
        // printf("YES\n");
        lastans = query(1, n, root[id[lk] - 1], root[id[rk]], k);
        printf("%d\n", lastans);
=======
const ll maxn=1000000;
class Splay{
    private:
        ll ch[maxn][2],f[maxn],size[maxn],cnt[maxn];
        ll sz,root;
        inline bool get(ll x){
            return ch[f[x]][1]==x;
        }
        inline void update(ll x){
            if (x){
                size[x]=cnt[x];
                if (ch[x][0]) size[x]+=size[ch[x][0]];
                if (ch[x][1]) size[x]+=size[ch[x][1]];
            }
        }
        inline void rotate(ll x){
            ll old=f[x],oldf=f[old],whichx=get(x);
            ch[old][whichx]=ch[x][whichx^1]; f[ch[old][whichx]]=old;
            ch[x][whichx^1]=old; f[old]=x;
            f[x]=oldf;
            if (oldf)
                ch[oldf][ch[oldf][1]==old]=x;
            update(old); update(x);
        }
        inline void splay(ll x){
            for (ll fa;fa=f[x];rotate(x))
              if (f[fa])
                rotate((get(x)==get(fa))?fa:x);
            root=x;
        }
    public:
        ll key[maxn];
        inline void clear(ll x){
            ch[x][0]=ch[x][1]=f[x]=size[x]=cnt[x]=key[x]=0;
        }
        void insert(ll x){
        if (root==0){sz++; ch[sz][0]=ch[sz][1]=f[sz]=0; root=sz; size[sz]=cnt[sz]=1; key[sz]=x; return;}
        ll now=root,fa=0;
        while(1){
            if (x==key[now]){
                cnt[now]++; update(now); update(fa); splay(now); break;
            }
            fa=now;
            now=ch[now][key[now]<x];
            if (now==0){
                sz++;
                ch[sz][0]=ch[sz][1]=0;
                f[sz]=fa;
                size[sz]=cnt[sz]=1;
                ch[fa][key[fa]<x]=sz;
                key[sz]=x;
                update(fa);
                splay(sz);
                break;
            }
        }
    }
    ll find(ll x){
        ll now=root,ans=0;
        while(1){
            if (x<key[now])
              now=ch[now][0];
            else{
                ans+=(ch[now][0]?size[ch[now][0]]:0);
                if (x==key[now]){
                    splay(now); return ans+1;
                }
                ans+=cnt[now];
                now=ch[now][1];
            }
        }
    }
    ll findx(ll x){
        ll now=root;
        while(1){
            if (ch[now][0]&&x<=size[ch[now][0]])
              now=ch[now][0];
            else{
                ll temp=(ch[now][0]?size[ch[now][0]]:0)+cnt[now];
                if (x<=temp) return key[now];
                x-=temp; now=ch[now][1];
            }
        }
    }
    ll pre(){
        ll now=ch[root][0];
        while (ch[now][1]) now=ch[now][1];
        return now;
    }
    ll next(){
        ll now=ch[root][1];
        while (ch[now][0]) now=ch[now][0];
        return now;
    }
    void del(ll x){
        ll whatever=find(x);
        if (cnt[root]>1){cnt[root]--; update(root); return;}
        if (!ch[root][0]&&!ch[root][1]) {clear(root); root=0; return;}
        if (!ch[root][0]){
            ll oldroot=root; root=ch[root][1]; f[root]=0; clear(oldroot); return;
        }
        else if (!ch[root][1]){
            ll oldroot=root; root=ch[root][0]; f[root]=0; clear(oldroot); return;
        }
        ll leftbig=pre(),oldroot=root;
        splay(leftbig);
        ch[root][1]=ch[oldroot][1];
        f[ch[oldroot][1]]=root;
        clear(oldroot);
        update(root);
    }
};
Splay F;
int main(){
    ll n,m,opt,x;
    scanf("%lld %lld",&n,&m);
    for(ll i=1;i<=n;i++)
    {
        scanf("%lld",&x);
        F.insert(x);
    }
    ll ans=0,lastans=0;
    for (ll i=1;i<=m;++i){
        scanf("%lld %lld",&opt,&x);
        x^=lastans;
        switch(opt){
            case 1: F.insert(x); break;
            case 2: F.del(x); break;
            case 3: lastans = F.find(x),ans ^= lastans; break;
            case 4: lastans = F.findx(x),ans ^= lastans; break;
            case 5: F.insert(x); lastans = F.key[F.pre()], ans ^= lastans; F.del(x); break;
            case 6: F.insert(x); lastans = F.key[F.next()], ans ^= lastans; F.del(x); break;
        }
>>>>>>> ff29dd63a7560b62f15a61b6e0d472024883dc07
    }
    return 0;
}