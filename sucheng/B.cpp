#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define int long long

signed main(){
    int t;
    int x,y,p,q;
    cin>>t;
    while(t--){
        cin>>x>>y>>p>>q;
        if(p==q){
            cout<<-1<<endl;
            continue;
        }
        else{
            int m=(y-x)/(q-p);
            if((y-x)-m*(q-p))m++;
            int m1=x/p;
            if(x-m1*p)m1++;
            int m2=y/q;
            if(y-m2*q)m2++;

            int m4=max(m,m1);
            m4=max(m4,m2);
           
            cout<<q*m4-y<<endl;
        }

    }
    return 0;
}


