#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+7;
int n,k,maxx;
int dp[maxn],a[maxn],ans[maxn];
int update(){
    int i=1;
    while(1){
        dp[i]=0x7fffffff;
        for(int j=1;j<=k && i-a[j]>=0;j++)
            dp[i]=min(dp[i],dp[i-a[j]]+1);
        if(dp[i] > n)
            break;
        i++;
    }
    i--;
    if(i>maxx){
        for(int j=1;j<=k;j++)
            ans[j]=a[j];
        return i;
    }
return maxx;
}
void dfs(int depth,int minn){
    if(depth>k){
        maxx=update();
        return;
    }
    for(int i=minn+1;i<=maxx+1;i++){//从小到大选择种类
        a[depth]=i;
        dfs(depth+1,i);
    }
}
int main(){
    scanf("%d %d",&n,&k);
    maxx=n;
    a[1]=1;
    dfs(2,1);
    for(int i=1;i<=k;i++)
        printf("%d ",ans[i]);
    cout<<endl;
    printf("MAX=%d",maxx);
return 0;
}