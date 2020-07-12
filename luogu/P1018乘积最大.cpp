#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+7;
#define ll long long
int n,k;
string s;
__int128_t dp[41][10];//dp[i][j]记录前i个数里面插入k个乘号的最大值
__int128_t sp[41][411];////sp[i][j]记录从i到j这一串数的值
int a[maxn];
void print(__int128_t x){
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
}
void init(){
    for(int i=0;i<=n;i++)
        for(int j=0;j<=k;j++)
            dp[i][j]=0;
}
int main(){
    init();
    scanf("%d %d",&n,&k);
    cin>>s;
    for(int i=0;i<s.length();i++){
        a[i+1]=s[i]-'0';
        sp[i+1][i+1]=a[i+1];
    }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            sp[i][j]=sp[i][j-1]*10+a[j];//sp存入

    for(int i=1;i<=n;i++)
        dp[i][0]=dp[i-1][0]*10+a[i];//预处理不加乘号的值
    
    for(int p=1;p<=k;p++)
        for(int i=p+1;i<=n;i++)//要插入p个乘号，最少也要p+1个数，i表示目前的总长度
            for(int j=p;j<i;j++)//在当前总长度内，插入新的乘号的位置
                dp[i][p]=max(dp[i][p],dp[j][p-1]*sp[j+1][i]);
    print(dp[n][k]);
return 0;
}
/*

*/