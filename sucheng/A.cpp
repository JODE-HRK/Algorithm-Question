#include <iostream>
#include <stdio.h>
using namespace std;
#define ll long long int


int cal(int fz,int fm){
    double d=1.0*fz/fm;
    if(d>0.5)return 500;
    if(d>0.25)return 1000;
    if(d>0.125)return 1500;
    if(d>0.0625)return 2000;
    if(d>0.03125)return 2500;
    else return 3000;
}

int a[125][5];
int flag[5];
int f[5];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;++i){
        for(int j=0;j<5;++j){
            cin>>a[i][j];
            if(a[i][j]>=0)f[j]++;
        }
    }
    
    for(int i=0;i<5;++i){
        if(a[1][i]==-1&&a[2][i]>=0)flag[i]=1;
        if(a[1][i]>=0&&a[2][i]>=0&&a[1][i]>a[2][i])flag[i]=1;
    }

    //for(int i=0;i<5;++i)cout<<flag[i]<<" ";

    ll sum1=0,sum2=0;
    for(int i=0;i<5;++i){
        if(flag[i]){
            if(a[1][i]>=0)sum1=sum1+2*(250-a[1][i]);
            if(a[2][i]>=0)sum2=sum2+2*(250-a[2][i]);
        }
        else{
            if(a[1][i]>=0)sum1=sum1+12*(250-a[1][i]);
            if(a[2][i]>=0)sum2=sum2+12*(250-a[2][i]);
        }
    }
    
    if(sum1<=sum2){
        cout<<-1<<endl;
        return 0;
    }
    
    return 0;
}