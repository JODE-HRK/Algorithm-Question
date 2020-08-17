#include <bits/stdc++.h>

#define mp make_pair
#define pb push_back
#define newline puts("")

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int Maxn = 1e5+10;
const int Inf = 0x7f7f7f7f;

struct GRAPH{
    int n,m;
    vector<pii> G;
    vector<int> V;
    bool Tree,Value;
    void operator = (const GRAPH &rhs){
        Tree = rhs.Tree, n = rhs.n, m = rhs.m;
        G.clear(), V.clear();
        for(auto vv: rhs.G)  G.pb(vv);
        for(auto vv: rhs.V)  V.pb(vv);
    }
};
ostream &operator<<(ostream &out,pii p){
	out<<p.first<<" "<<p.second;
	return out;
}
ostream &operator<<(ostream &out,vector<pii> vp){
	for(auto vv:vp)  out<<vv<<endl;
	return out;
}
ostream &operator<<(ostream &out,vector<int> v){
	for(auto vv:v)  out<<vv<<" ";
	return out;
}
ostream &operator<<(ostream &out,GRAPH Map){
    if( Map.Tree )  out<<Map.n<<endl;
    else out<<Map.n<<" "<<Map.m<<endl;
    for(int i=0;i<Map.m;i++)
    {
        if( Map.Value )  out<<Map.G[i]<<" "<<Map.V[i]<<endl;
        else out<<Map.G[i]<<endl;
    }
	return out;
}

// 最大值定义 例如随机生成的 边权,序列,坐标 中的最大值
const int MAX_NUM = 10;
// 生成一个 [l,r] 中的数 采用二分
int Int(int l,int r);
// 生成一个长度为 n 序列
vector<int> Array(int n);
// 生成一个长度为 n 的排列 洗牌算法
vector<int> Permutation(int n);
// 生成一棵点数量为 n 树 , 默认无边权 需要边权 flag 应为 true
GRAPH Tree(int n,bool flag);
// 生成一个 n 个点 m 条边的图 默认无边权 需要边权 flag 应为 true 保证在无向图下联通
GRAPH Graph(int n,int m,bool flag);
// 生成 n 个二维平面的点
vector<pii> Points(int n);

int Int(int l,int r){
    int ans = l+rand()%(r-l+1);
    while( l <= r ){
        int mid = (l+r) >> 1;
        if( rand()&1 )  ans = mid, r = mid-1;
        else l = mid+1;
    }
    return ans;
}
vector<int> Array(int n){
    vector<int> v;
    for(int i=1;i<=n;i++)
        v.pb(Int(1,MAX_NUM));
    return v;
}
vector<int> Permutation(int n){
    vector<int> v;
    for(int i=1;i<=n;i++)
        v.push_back(i);
    for(int i=0;i<n;i++)
        swap(v[i],v[rand()%(i+1)]);
    return v;
}
GRAPH Tree(int n,bool flag = false){
    GRAPH Map;
    Map.Tree = true, Map.n = n ,Map.m = n-1, Map.Value = flag;
    vector<int> v = Permutation(n);
    for(int i=1;i<n;i++)
        Map.G.pb(mp(v[i],v[rand()%i]));
    if( flag )  Map.V = Array(n-1);
    return Map;
}
GRAPH Graph(int n,int m = -1,bool flag = false){
    GRAPH Map;
    if( m == -1 )  m = Int(n+2,3*n);
    Map.n = n, Map.m = m, Map.Tree = false, Map.Value = flag;
    vector<int> v = Permutation(n);
    for(int i=1;i<n;i++)
        Map.G.pb(mp(v[i],v[rand()%i]));
    for(int i=n;i<=m;i++)
        Map.G.pb(mp(rand()%n+1,rand()%n+1));
    if( flag )  Map.V = Array(m);
    return Map;
}
vector<pii> Points(int n){
    vector<pii> vp;
    for(int i=1;i<=n;i++)
        vp.pb(mp(rand()%MAX_NUM+1,rand()%MAX_NUM+1));
    return vp;
}

int main(){
    srand((unsigned)time(NULL));
    /*
// 输出一个 [10,20] 中的数
    cout<<Int(10,20)<<endl;
// 输出一个长度为 6 的序列
    cout<<Array(6)<<endl;
// 输出一个长度为 6 的排列
    cout<<Permutation(6)<<endl;
// 输出一颗 5 个点的 无边权的树
    cout<<Tree(5)<<endl;
// 输出一颗 5 个点的 有边权的树
    cout<<Tree(5,true)<<endl;
// 输出一个 5个点 8条边的图 无边权
    cout<<Graph(5,8)<<endl;
// 输出 5 个点
    cout<<Points(5)<<endl;
    // */
    return 0;
}