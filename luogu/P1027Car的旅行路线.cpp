#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+7;
int n,s,t,cnt=0,A,B;
int tw[101];
double w[401][401];
struct Node{
    int x,y;
}air[maxn];
double getw(int st,int en,int pur){
    return sqrt(abs(air[st].x-air[en].x)*abs(air[st].x-air[en].x)+abs(air[st].y-air[en].y)*abs(air[st].y-air[en].y))*(double)pur;
}
void getleast(){
    int xx1=air[cnt].x,xx2=air[cnt-1].x,xx3=air[cnt-2].x,yy1=air[cnt].y,yy2=air[cnt-1].y,yy3=air[cnt-2].y;
    ++cnt;
    if((xx2-xx1)*(xx3-xx1)+(yy2-yy1)*(yy3-yy1)==0)
        air[cnt].x=xx2+xx3-xx1,air[cnt].y=yy2+yy3-yy1;
    else if((xx1-xx3)*(xx2-xx3)+(yy1-yy3)*(yy2-yy3)==0)
        air[cnt].x=xx2+xx1-xx3,air[cnt].y=yy2+yy1-yy3;
    else
        air[cnt].x=xx1+xx3-xx2,air[cnt].y=yy1+yy3-yy2;
}
void debug(){
    for(int i=1;i<=cnt;i++)
        for(int j=i+1;j<=cnt;j++)
            printf("%d %d %.1lf\n",i,j,w[i][j]);
    cout<<endl;
}
int main(){
    scanf("%d",&n);
    while (n--){
        fill(w[0],w[0]+401*401,maxn);
        scanf("%d %d %d %d",&s,&t,&A,&B);
        for(int i=1;i<=s;i++){
            for(int j=1;j<=3;j++){
                ++cnt;
                scanf("%d %d",&air[cnt].x,&air[cnt].y);
            }
            scanf("%d",&tw[i]);
            getleast();
            if(i==A || i==B)
                for(int j=cnt-3;j<=cnt;j++)
                    for(int k=cnt-3;k<=cnt;k++)
                      w[j][k]=w[k][j]=0;
            else {
                for(int j=cnt-3;j<=cnt;j++)
                    for(int k=cnt-3;k<=cnt;k++)
                        w[j][k]=w[k][j]=getw(j,k,tw[i]);
            }
        }
        //debug();
        for(int i=1;i<=cnt;i++)
            for(int j=1;j<=cnt;j++)
                if(w[i][j]>100000)
                    w[i][j]=w[j][i]=getw(i,j,t);
                else if(i==j)
                    w[i][j]=w[j][i]=0;
        for(int k=1;k<=cnt;k++)
            for(int i=1;i<=cnt;i++)
                for(int j=1;j<=cnt;j++)
                    if(i!=j && i!=k && j!=k){
                        w[j][i]=w[i][j]=min(w[i][j],w[i][k]+w[k][j]);
                        // if(abs(w[i][j]-204.7)<0.1)
                        //     printf("%d %d %d\n",i,k,j);
                        // if(i==1 && j==5)
                        //     printf("%d %d %d %lf\n\n%lf %lf\n\n",i,k,j,w[i][j],w[i][k],w[k][j]);
                    }
        double ans=maxn;
        for(int i=4*(A-1)+1;i<=4*A;i++)
            for(int j=4*(B-1)+1;j<=4*B;j++)
                ans=min(w[i][j],ans);
        printf("%.1lf\n",ans);
    }
return 0;
}