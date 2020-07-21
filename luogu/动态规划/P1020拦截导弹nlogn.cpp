#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+7;
queue <int> Q;
int cnt=0,hi[maxn],k,dp[maxn],f[maxn],ans=1,ti=1;
void getans(){
    f[1]=dp[1]=hi[1];
    for(int i=2;i<=cnt;i++)
    {
            if( f[ans] >= hi[i])
                f[++ans]=hi[i];
            else{
                int tmp=upper_bound(f+1,f+1+ans,hi[i],greater<int>())-f;//greater相当于一个比较函数，return a<b;
                //即找到f这个下降序列中第一个小于hi[i]的数的位置，然后替换他
                f[tmp]=hi[i];
            }
            if(dp[ti] < hi[i])
                dp[++ti]=hi[i];
            else{
                int tmp=lower_bound(dp+1,dp+1+ti,hi[i])-dp;
                dp[tmp]=hi[i];
            }
    }
}
int main(){
    //freopen(".in","r",stdin);
    memset(dp,0,sizeof(dp));
    memset(f,0,sizeof(f));
    while(~scanf("%d",&k)){
        hi[++cnt]=k;
    }
    getans();
    printf("%d\n%d",ans,ti);
return 0;
}