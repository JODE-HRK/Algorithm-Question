#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int p=50331653;
const int maxn=1e5+7;
char k;
int n,start,cnt[maxn],ans=0;
char str[maxn];
ull po[maxn];
struct WO{
    int len;
    ull hash[maxn];
}word[21];
void prex(){
    memset(cnt,0,sizeof(cnt));
    po[0]=1;
    for(int i=1;i<=maxn;i++)
        po[i]=po[i-1]*p;
}
void pre(int pi){
    scanf("%s",str);
    word[pi].hash[0]=str[0]-'a'+1;
    int l=word[pi].len=strlen(str);
    for(int i=1;i<l;i++){
        word[pi].hash[i]=word[pi].hash[i-1]*p+(str[i]-'a'+1);
    }
}
ull gethash(int pi,int l,int r){
    if(l==0)
        return word[pi].hash[r];
    return word[pi].hash[r]-word[pi].hash[l-1]*po[r-l+1];
}
void dfs(int z,int lasti){
    ans=max(ans,z);
    for(int i=1;i<=n;i++)
    if(cnt[i]<2){
        for(int j=0;j<min(word[lasti].len,word[i].len);j++){
            if(gethash(i,0,j) == gethash(lasti,word[lasti].len-j-1,word[lasti].len-1)){
                cnt[i]++;
                dfs(z+word[i].len-j-1,i);
                cnt[i]--;
            }
        }
    }
}
int main(){
    prex();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        pre(i);
    scanf(" %c",&k);
    start=k-'a'+1;
    for(int i=1;i<=n;i++)
    if(start == gethash(i,0,0)){
        cnt[i]++;
        dfs(word[i].len,i);
        cnt[i]--;
    }
    printf("%d",ans);
return 0;
}