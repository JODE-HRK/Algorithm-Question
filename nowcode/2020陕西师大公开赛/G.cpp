#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e4+7;
struct Dish{
	int happy,money;
}a[maxn],tmp;
int n,m,tot=0;
int lg[maxn];
int dp[1401][maxn];//先物品，后参数
int main(){
	int tp = 1;
	lg[0]=1;
	while(lg[tp-1]*2 <= 10000){
		lg[tp] = lg[tp-1] * 2;
		++tp;
	}
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&tmp.happy,&tmp.money);
		tp = 0;
		a[++tot] = tmp;
		while(tmp.happy>lg[tp]){
			tmp.happy -= lg[tp];
			a[++tot] = tmp;
			tmp.happy += lg[tp];
			++tp;
		}
	}
	dp[0][0] =0 ;
	for(int i=1;i<=tot;i++){
		for(int j=0;j<=m;j++)
		if(a[i].money<=j)
			dp[i][j] = max(dp[i-1][j],dp[i-1][j-a[i].money]+a[i].happy);
		else	
			dp[i][j] = dp[i-1][j];
	}
	printf("%d",dp[tot][m]);
	return 0;
}