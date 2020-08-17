#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5+7;
int n,block,q;
int a[maxn];
int cnt[3000000];
int zans[maxn];
struct PRO{
    int l,r,id,sp;
    bool operator < (const PRO x){
        if(sp == x.sp)
            return r<x.r;
        return sp<x.sp;
    }
}pro[maxn];
inline int read(){
    char c = getchar();int x = 0,fh = 0;
    while(c < '0' || c > '9'){fh |= c == '-';c = getchar();}
    while(c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}
    return fh?-x:x;
}
int getnum(int x){
    int tmp = 1;
    // printf("%d\n",len);
    for(int i=2;i*i<=abs(x);i++){
        while(x%(i*i) == 0)
           x/=(i*i);
    }
    // printf("x:%d tmp:%d\n",x,tmp);
return x/tmp;
}
int calc(int x){
    return x*(x-1)/2;
}
void work(int &ans,int val,int pos,int &cnt0){
    if(a[pos] == 0)
        cnt0+=val;
    else{
        ans -= calc(cnt[a[pos]+1000000]);
        cnt[a[pos]+1000000]+=val;
        ans += calc(cnt[a[pos]+1000000]);
    }
}
int main(){
    n =read();
    for(int i=1;i<=n;i++)
        a[i] = read(),a[i] = getnum(a[i]),cnt[a[i]]=0;
    // for(int i=1;i<=n;i++)
    //     printf("%d ",a[i]);
    // cout<<endl;
    block = sqrt(n);
    q = read();
    pro[0].l = pro[0].r =0;
    for(int i = 1;i<=q;i++){
        pro[i].l = read(),pro[i].r = read();
        pro[i].id = i;
        pro[i].sp = (pro[i].l-1)/block + 1;
    }
    sort(pro+1,pro+1+q);
// printf("YES\n");
    int l=1,r=0,ans=0,cnt0=0;
    for(int i=1;i<=q;i++){
        while(l>pro[i].l)
            work(ans,1,--l,cnt0);
        while(r<pro[i].r)
            work(ans,1,++r,cnt0);
        while(l<pro[i].l)
            work(ans,-1,l++,cnt0);
        while(r>pro[i].r)
            work(ans,-1,r--,cnt0);
        zans[pro[i].id] = ans+cnt0*(r-l) - calc(cnt0);
        // lastcnt0 = cnt0;
    }
    for(int i=1;i<=q;i++)
        printf("%d\n",zans[i]);
    return 0;
}