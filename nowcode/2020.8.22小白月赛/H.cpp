#include <bits/stdc++.h>
using namespace std;
int n,m,p;
int sum[501][501][26];
char s[501];
bool judge(int i,int j,int mid){
	int rxx = i+mid-1,rxy = j+mid-1;
	for(int k=0;k<26;k++)
	if(sum[rxx][rxy][k] - sum[rxx][j-1][k] - sum[i-1][rxy][k] + sum[i-1][j-1][k] > p)
		return 0;
return 1;
}
int main(){
	scanf("%d %d %d",&n,&m,&p);
	// memset(sum,0,sizeof(sum));
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		for(int j=1;j<=m;j++){
			sum[i][j][s[j-1]-'a']++;
		}
	}
	for(int k=0;k<26;k++)
    	for(int i=1;i<=n;i++)
    		for(int j=1;j<=m;j++)
     			sum[i][j][k] += sum[i][j-1][k];
    for(int k=0;k<26;k++)
    	for(int j=1;j<=m;j++)
    		for(int i=1;i<=n;i++)
        		sum[i][j][k] += sum[i-1][j][k];

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
		{
			int l = 1,r = min(n-i+1,m-j+1),tans=1;
			while(l<=r){
				int mid = (l+r)>>1;
				if(judge(i,j,mid))
					tans = mid,l=mid+1;
				else	
					r = mid-1;
			}
			printf("%d ",tans);
		}
		cout<<endl;
	}
return 0;
}