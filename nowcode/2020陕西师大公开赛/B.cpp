#include <bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int maxn = 4e5+7;
int n;
int g[101][101];
int dis[101][101];
bool vis[101][101];
int Movx[4] = {0,1,0,-1};
int Movy[4] = {1,0,-1,0};
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&g[i][j]),dis[i][j] = 0x7fffffff;
    dis[1][1]=g[1][1];
    queue<pii> Q;
    Q.push((pii){1,1});
    while(!Q.empty()){
        pii now = Q.front();
        Q.pop();
        int xx = now.first,yy = now.second;
        if(vis[xx][yy])
            continue;
        vis[xx][yy]=1;
        for(int i=0;i<4;i++){
            int x = xx + Movx[i],y = yy+Movy[i];
            if(g[x][y]<=0 || x<=0 || x>n || y<=0 || y>n)
                continue;
            dis[x][y] = min(dis[xx][yy] + g[x][y],dis[x][y]);
            Q.push((pii){x,y});
        }
    }
    if(dis[n][n]==0x7fffffff)
        printf("0");
    else
        printf("%d",dis[n][n]);
return 0;
}
/*
1
2
3
6
4
5
2
3
6
4
5
*/