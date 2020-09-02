#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define ll long long int

struct node{
    double x;
    double y;
}p[60];

double getArea(node *p,int m){
    double s=0.0; 
    for(int i=0;i<m;++i)
        s+=p[i].x*p[(i+1)%m].y-p[i].y*p[(i+1)%m].x;
    return fabs(s/2.0);
}

int main(){
    int n;
    cin>>n;
    int m;
    double ans=0.0;
    while(n--){
        scanf("%d",&m);
        for(int i=0;i<m;++i){
            scanf("%lf%lf",&p[i].x,&p[i].y);
        }
        ans=ans+getArea(p,m);
    }
    cout<<(ll)ans<<endl;
    return 0;
}