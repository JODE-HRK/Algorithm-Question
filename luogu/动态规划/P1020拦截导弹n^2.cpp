#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+7;
queue <int> Q;
int cnt=0,hi[maxn],k,dp[maxn],f[maxn],ans=1,ti=1;
void getans(){
    for(int i=2;i<=cnt;i++)
    {
        for(int j=1;j<i;j++){
            if(hi[j] >= hi[i])
                f[i]=max(f[j]+1,f[i]);
            if(hi[j] < hi[i])
                dp[i]=max(dp[j]+1,dp[i]);
        }
        ans=max(ans,f[i]);
        ti=max(ti,dp[i]);
    }
}
int main(){
    // freopen(".in","r",stdin);
    while(~scanf("%d",&k)){
        hi[++cnt]=k;
        dp[cnt]=f[cnt]=1;
    }
    getans();
    printf("%d\n%d",ans,ti);
return 0;
}