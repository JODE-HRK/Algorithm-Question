#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5+7;
int kmp(string s1,string s2,int id)
{
    int l1 = s1.length(), l2 = s2.length();
    int k2=0;
    for(int i=0;i<l1;i++)
    {
        if(s2[k2] == s1[i])
            k2++;
        if(k2==l2)
            return 1;
    }
return 0;
}
int n,m;
string t[1001],s[101];
int main(){
    scanf("%d %d",&n,&m);   
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    int ans;
    for(int i=1;i<=m;i++)
        cin >> s[i];
    for(int i=1;i<=n;i++){
        ans=0;
        for(int j=1;j<=m;j++)
            ans+=kmp(t[i],s[j],j);
        printf("%d\n",ans);
    }
return 0;
}