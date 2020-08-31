#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;


int day[2020];
int last[2020];
int pe[2020];
int main(){
    int m,n,w,h;
    scanf("%d%d%d%d",&m,&n,&w,&h);

    for(int i=1;i<=m;++i){
        scanf("%d",&pe[i]);
        pe[i]/=w;    
    }

    for(int i=1;i<=n;++i)scanf("%d",&day[i]);

    

    return 0;
}