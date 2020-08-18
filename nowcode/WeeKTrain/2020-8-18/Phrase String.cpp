    #include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5+7;
const int mod = 1e9+7;
ll n,m;
ll poww(ll base, ll power) //此处的power是 mod-2
{
    ll ans = 1;
    while (power)
    {
        if (power & 1)
            ans = ans * base % (1ll * mod);
        power >>= 1;
        base = (base * base) % (1ll * mod);
    }
    return ans;
}
int main(){
    scanf("%lld %lld",&n,&m);
    ll ans=0;
    ll st=0;
    if(m>n)
        ans = poww(1ll*2,m)-1;
    else{
        int mid =n/2;
        int tmp=mid;
        while(m>2){
            ans= (ans + poww(1ll*2,1ll*tmp-1+st) % mod + poww(1ll*2,1ll*n - tmp+st))%mod;
            tmp--;
            m-=2;
        }
        ans = (ans + poww(1ll*2,1ll*st) % mod + poww(1ll*2,1ll*n-1+st)) % mod;
    }
    printf("%lld",ans);
return 0;
}