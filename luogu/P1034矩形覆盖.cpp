#include <bits/stdc++.h>
#define ull unsigned long long 
using namespace std;
const int maxn=1e2+7;
int n,k,ans=0x7fffffff;
struct Node{
    int x,y,id;
}node[maxn];
bool cmp(Node xx,Node yy){
    if(xx.x==yy.x)
        return xx.y<yy.y;
    return xx.x<yy.x;
}
bool cmp1(Node xx,Node yy){
    if(xx.y==yy.y)
        return xx.x<yy.x;
    return xx.y<yy.y;
}
void dfs(int ctk,int sum,int tp,Node n1[maxn],Node n2[maxn]){
    if(ctk>k || sum>ans)
        return;
    if(tp>n){
        if(ctk==k)
            ans=min(sum,ans);
        return;
    }
    int downx=0x7fffffff,downy=0x7fffffff,upx=-1,upy=-1;
    sort(n1+tp,n2+1+n,cmp);
    for(int i=tp;i<=n;i++){
        downx=min(node[i].x,downx);
        downy=min(node[i].y,downy);
        upx=max(node[i].x,upx);
        upy=max(node[i].y,upy);
        dfs(ctk+1,sum+(upx-downx)*(upy-downy),i+1,n1,n2);
    }
    downx=0x7fffffff,downy=0x7fffffff,upx=-1,upy=-1;
    sort(n2+tp,n2+n+1,cmp1);
    for(int i=tp;i<=n;i++){
        downx=min(node[i].x,downx);
        downy=min(node[i].y,downy);
        upx=max(node[i].x,upx);
        upy=max(node[i].y,upy);
        dfs(ctk+1,sum+(upx-downx)*(upy-downy),i+1,n1,n2);
    }
}
int main(){
    //freopen(".in","r",stdin);
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&node[i].x,&node[i].y);
        node[i].id=i;
    }
    dfs(0,0,1,node,node);
    printf("%d",ans);
return 0;
}