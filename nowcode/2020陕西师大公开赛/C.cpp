#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5+7;
const int mod = 998244353;
ll n,m;
ll multi[maxn],fmulti[maxn];
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
void init(){
	multi[0] = 1;
	for(int i=1;i<=maxn;i++)
		multi[i] = multi[i-1] * i % mod;
	fmulti[maxn] = poww(multi[maxn],mod-2);
	for(int i=maxn-1;i>=0;i--)
		fmulti[i] = fmulti[i+1] * (i+1) % mod;
}
ll C(ll a,ll b){
	if(a<b)
		return 0;
	return multi[a] * fmulti[b] % mod * fmulti[a-b] %mod;
}
int main(){
	init();
	scanf("%lld %lld",&n,&m);
	if(n==2){
		printf("0");
		return 0;	
	}
	ll zans = C(m,n-1) %mod * (n-2) %mod * poww(2,n-3) %mod;
	printf("%lld",zans);
	return 0;
}