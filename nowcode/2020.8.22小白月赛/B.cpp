#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+7;
int n;
int a[maxn];
int main(){
    a[0] = 0x7fffffff;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(a[i]>n)
        {
            printf("-1");
            return 0;
        }
    }
    sort(a+1,a+1+n);
    int ans = 0,i;
    for(i=n;i>=1;)
    {
        // printf("%d\n",i);
        if(a[i]<=0){
            i=0;
            ans += i;
            break;
        }
        if(i>=a[i])
            i=i-a[i], ans++;
        else i--;
    }
    printf("%d",ans);
return 0;
}