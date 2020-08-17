#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 5e4+7;
int n,m,k;
int a[maxn];
int Blo[300][maxn],c[maxn];
ll ANS[maxn];
struct Pro{
    int l,r,blo,id;
    bool operator < (const Pro x)const{
        if(blo == x.blo)
            return r<x.r;
        return blo<x.blo;
    }
}pro[maxn];
int main(){
    scanf("%d %d %d",&n,&m,&k);
    int block = sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        Blo[(i-1)/block+1][a[i]]++;
    }
    // printf("YES\n");
    for(int i=1;i<=m;i++){
        scanf("%d %d",&pro[i].l,&pro[i].r);
        pro[i].blo = (pro[i].l-1)/block+1;
        pro[i].id = i;
    }
    sort(pro+1,pro+1+m);
    int l=1,r=0;
    ll tans=0;
    for(int i=1;i<=m;i++){
        while(l>pro[i].l)
            --l,++c[a[l]],tans += 2*c[a[l]] - 1;//平方差公式的转换
        while(r<pro[i].r)
            ++r,++c[a[r]],tans += 2*c[a[r]] - 1;
        while(l<pro[i].l)
            --c[a[l]],tans -= 2*c[a[l]] + 1,++l;
        while(r>pro[i].r)
            --c[a[r]],tans -= 2*c[a[r]] + 1,--r;
        ANS[pro[i].id] = tans;
    }
    for(int i=1;i<=m;i++)
        printf("%lld\n",ANS[i]);
return 0;
}