#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e7+7;
int n;
char a[maxn];
int sum[26];
int main(){
    scanf("%d",&n);
    scanf("%s",a);
    // cout<<str;
    int ans=0;
    for(int i=0;i<n;i++){
        sum[a[i]-'a']++;
    }
    int ts = min(min(sum['i'-'a'],sum['n'-'a']),sum['g'-'a']);
    int tk = sum['k'-'a'];
    //printf("%d %d\n",tk,ts);
    if(tk*2<=ts)
        ans = tk*2;
    else
        ans = ts;
    printf("%d",ans);
return 0;
}