#include <bits/stdc++.h>
using namespace std;
const int maxn=101;
int n,m,num[maxn],dp1[maxn][maxn][maxn],dp2[maxn][maxn][maxn],sum[maxn];
int getmod(int s){
     return ((s%10)+10)%10;
}
int main(){
    freopen(".in","r",stdin);
    memset(dp2,0x7F,sizeof(dp2));
    sum[0]=0;
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&num[i]),sum[i]=sum[i-1]+num[i];
    for(int i=n+1;i<=2*n;i++)
        num[i]=num[i-n],sum[i]=sum[i-1]+num[i];
    for(int i=1;i<=2*n;i++)
        for(int j=i;j<=2*n;j++)
            dp2[i][j][1]=dp1[i][j][1]=getmod(sum[j]-sum[i-1]);
    
    for(int i=2;i<=m;i++)//枚举分段数
        for(int l=1;l<=2*n;l++)//枚举起点
            for(int r=l+i-1;r<=2*n;r++)//l+i-1最少要这么长，枚举终点
                for(int d=l+i-2;d<r;d++){//枚举断点
                    dp1[l][r][i]=max(dp1[l][r][i],dp1[l][d][i-1]*getmod(sum[r]-sum[d]));
                    dp2[l][r][i]=min(dp2[l][r][i],dp2[l][d][i-1]*getmod(sum[r]-sum[d]));
                }
        int ansmax=-1,ansmin=0x7fffffff;
        for(int i=1;i<=n;i++){
            ansmax=max(ansmax,dp1[i][i+n-1][m]);
            ansmin=min(ansmin,dp2[i][i+n-1][m]);
        }
        printf("%d\n%d",ansmin,ansmax);
return 0;
}