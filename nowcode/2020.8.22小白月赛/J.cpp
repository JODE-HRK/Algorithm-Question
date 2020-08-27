#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int n;
char a[101][100001];
int d[maxn],sum=0;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",a[i]),d[i] = a[i][strlen(a[i])-1] - '0',sum+=d[i];
    if(sum%2==0)
        printf("0\n");
    else
        printf("1\n");
return 0;
}