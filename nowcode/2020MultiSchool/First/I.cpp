/*
 * @Descripttion: 
 * @version: 
 * @Author: JODEHRK
 * @Date: 2020-07-14 11:01:05
 * @LastEditors: JODEHRK
 * @LastEditTime: 2020-07-14 11:01:17
 */ 
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define N 306
#define M 4005
using namespace std;
int n,m,D[N];
int zz,a[N];
struct ro{
    int to,next;
}road[M];
void build(int x,int y)
{
    zz++;
    road[zz].to=y;
    road[zz].next=a[x];
    a[x]=zz;
}
int fa[N],bj[N],pre[N],to[N],cnt2;
queue<int> q1;
int find(int x)
{
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
int cnt,dfn[N];
int get_lca(int x,int y)
{
    cnt++;
    x=find(x),y=find(y);
    while(dfn[x]!=cnt)
    {
        dfn[x]=cnt;
        x=find(pre[to[x]]);
        if(y) swap(x,y);
    }
    return x;
}
void work2(int x,int y,int z)
{
    while(find(x)!=z)
    {
        pre[x]=y,y=to[x];
        if(bj[y]==2) bj[y]=1,q1.push(y);
        if(find(x)==x) fa[x]=z;
        if(find(y)==y) fa[y]=z;
        x=pre[y];
    }
}
bool bfs(int S)
{
    for(int i=1;i<=n*2+m*2;i++)
    {
        fa[i]=i,bj[i]=pre[i]=0;
    }
    while(!q1.empty())q1.pop();
    q1.push(S);bj[S]=1;
    while(!q1.empty())
    {
        int x=q1.front();q1.pop();
        for(int i=a[x];i;i=road[i].next)
        {
            int y=road[i].to;
            if(find(y)==find(x)||bj[y]==2)continue;
            if(!bj[y])
            {
                bj[y]=2,pre[y]=x;
                if(!to[y])
                {
                    for(int now=y,la;now!=0;now=la)
                    {
                        la=to[pre[now]],to[now]=pre[now],to[pre[now]]=now;
                    }
                    return 1;
                }
                bj[to[y]]=1;q1.push(to[y]);
            }
            else
            {
                int lca=get_lca(x,y);
                work2(x,y,lca);
                work2(y,x,lca);
            }
        }
    }
    return 0;
}
bool work()
{
    memset(dfn,0,sizeof(dfn));
    cnt=0;
    memset(to,0,sizeof(to));
    for(int i=1;i<=n*2+m*2;i++)
    {
        if(!to[i]) bfs(i);
    }
    int ans=0;
    for(int i=1;i<=n*2+m*2;i++) if(to[i]) ans++;
    return ans==cnt2;
}
int deg[N];
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        zz=0;
        memset(a,0,sizeof(a));
        cnt2=n;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&D[i]);
            if(D[i]==2)cnt2++;
        }
        memset(deg,0,sizeof(deg));
        cnt2+=m*2;
        for(int i=1;i<=m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            deg[x]++,deg[y]++;
            if(D[x]==2)
            {
                build(x,2*n+i);
                build(x+n,2*n+i);
                build(2*n+i,x);
                build(2*n+i,x+n);
            }
            else
            {
                build(x,2*n+i);
                build(2*n+i,x);
            }
            if(D[y]==2)
            {
                build(2*n+m+i,y);
                build(2*n+m+i,y+n);
                build(y,2*n+m+i);
                build(y+n,2*n+m+i);
            }
            else
            {
                build(y,2*n+m+i);
                build(2*n+m+i,y);
            }
            build(2*n+i,2*n+m+i);
            build(2*n+m+i,2*n+i);
        }
        bool op=1;
        for(int i=1;i<=n;i++)
        {
            if(deg[i]<D[i])
            {
                op=0;
            }
        }
        if(!op)
        {
            printf("No\n");
            continue;
        }
        if(work())printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}