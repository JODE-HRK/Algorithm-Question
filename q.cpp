#include <bits/stdc++.h>

#define ed end()
#define bg begin()
#define mp make_pair
#define pb push_back
#define all(x) x.bg,x.ed
#define newline puts("")
#define si(x) ((int)x.size())
#define rep(i,n) for(int i=1;i<=n;++i)
#define rrep(i,n) for(int i=0;i<n;++i)
#define srep(i,s,t) for(int i=s;i<=t;++i)
#define drep(i,s,t) for(int i=t;i>=s;--i)

#define DEBUG
#define d1(x) std::cout << #x " = " << (x) << std::endl
#define d2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i <= to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }


#define L t<<1
#define R L|1
#define l(a) ST[a].l
#define r(a) ST[a].r
#define g(a) ST[a].gcd

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int Maxn = 2e6+10;
const int Inf = 0x7f7f7f7f;
const ll Inf_ll = 1ll*Inf*Inf;
const int Mod = 1e9+7;
const double eps = 1e-7;
struct Segment_tree{
    int l,r,gcd;
}ST[Maxn<<2];
int a[Maxn];
ll gcd(ll a,ll b){
    return b == 0 ? a : gcd(b,a%b);
}
void pushup(int t){
    g(t) = gcd(g(L),g(R));
}
void build(int t,int l,int r){
    l(t) = l, r(t) = r;
    if( l == r )
    {
        g(t) = a[l];
        return ;
    } 
    int mid = (l+r) >> 1;
    build(L,l,mid); build(R,mid+1,r);
    pushup(t);
}
int query(int t,int l,int r){
    // cout<<t<<" "<<l<<" "<<r<<endl;
    if( r(t) < l || r < l(t) )  return 0;
    if( l <= l(t) && r(t) <= r )  return g(t);
    int lg = query(L,l,r), rg = query(R,l,r);

    return gcd(lg,rg);
}
int vis[Maxn];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        if( a[i] == 1 )
        {
            puts("1");
            return 0;
        }
    }
    build(1,1,n);
    int l = 1, r = 0, ans = 0, Max = 0, Gcd = 0;
    while( 233 )
    {
        // d2(l,r); d1(Gcd);
        if( Gcd == 1 )
        {
            while( Gcd == 1 )
            {
                vis[a[l]]--;
                l++;
                Gcd = query(1,l,r);
            }
            continue;
        }
        else if( vis[Gcd] )
        {
            int Len = r-l+1;
            // cout<<"2 "<<l<<" "<<r<<endl;
            if( Len == Max )  ans++;
            else if( Len > Max )  Max = Len, ans = 1;
        }
        
        if( r < n )
        {
            r++;
            vis[a[r]]++;
            Gcd = gcd(Gcd,a[r]);
            // cout<<Gcd<<endl;
        }
        else break;
    }
    // d1(Max);
    cout<<ans<<endl;
    return 0;
}