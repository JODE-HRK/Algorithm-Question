#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+7;
int n,m,tot=0,k=0;
int fat[maxn];//并查集
struct Node{
    int fr,to,dis;
    bool operator <(const Node x)const{
        return dis<x.dis;
    }
}Edge[maxn];
int fa(int x){
    if(fat[x]!=x)
        return fa(fat[x]);
    return x;
}
void connect(int x,int y){
    fat[fa(y)]=fa(x);
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d %d %d",&Edge[i].fr,&Edge[i].to,&Edge[i].dis);
    for(int i=1;i<=n;i++)
        fat[i]=i;//并查集初始化
    sort(Edge+1,Edge+1+m);//将边按权值排序
    for(int i=1;i<=m;i++){
        if(k==n-1)    break;//边数达到n-1时就退出
        if(fa(Edge[i].fr) != fa(Edge[i].to)){
            connect(Edge[i].fr,Edge[i].to);//将两个点用并查集连接起来
            tot+=Edge[i].dis;//加上加入边的边权
            k++;//边数++
        }
    }
    printf("%d",tot);//输出最小生成树的权值
return 0;
}