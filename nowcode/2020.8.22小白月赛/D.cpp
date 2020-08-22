#include <bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int maxn = 2e5+7;
int n,q;
struct Node{
    int maxx,minn;
}tree[maxn<<4];
void build(int l,int r,int node){
    if(l==r){
        scanf("%d",&tree[node].maxx);
        tree[node].minn = tree[node].maxx;
        return;
    }
    int mid = (l+r)>>1;
    build(l,mid,node<<1);
    build(mid+1,r,node<<1|1);
    tree[node].minn = min(tree[node<<1].minn,tree[node<<1|1].minn);
    tree[node].maxx = max(tree[node<<1].maxx,tree[node<<1|1].maxx);
}
void change(int l,int r,int node,int x,int y){
    if(r < x || l > x)
        return;
    if(l==r){
        tree[node].maxx = y;
        tree[node].minn = y;
        return;
    }
    int mid = (l+r)>>1;
    change(l,mid,node<<1,x,y);
    change(mid+1,r,node<<1|1,x,y);
    tree[node].minn = min(tree[node<<1].minn,tree[node<<1|1].minn);
    tree[node].maxx = max(tree[node<<1].maxx,tree[node<<1|1].maxx);
}
pii search(int l,int r,int node,int le,int ri){
    pii tmp  = make_pair(0x7fffffff,0);
    if(ri < l || le > r)
        return tmp;
    if(le<=l && r<=ri){
        return make_pair(tree[node].minn, tree[node].maxx);
    }
    int mid = (l+r)>>1;
    pii ans1,ans2;
    ans1 = search(l,mid,node<<1,le,ri);
    ans2 = search(mid+1,r,node<<1|1,le,ri);
    tmp.second = max(ans1.second,ans2.second),tmp.first = min(ans1.first,ans2.first);
    return tmp;
}
int main(){
    scanf("%d %d",&n,&q);
    build(1,n,1);
    while(q--){
        int opt;
        scanf("%d",&opt);
        if(opt==1){
            int x,y;
            scanf("%d %d",&x,&y);
            change(1,n,1,x,y);
        }
        else{
            int l,r;
            scanf("%d %d",&l,&r);
            pii ans = search(1,n,1,l,r);
            if((ans.second-ans.first)==(r-l))
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
return 0;
}