#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int Inf=1e7;

int a[80],b[80];
char s[80];
int main(){
    int n;
    cin>>n;cin>>s;
    
    for(int i=0;i<n;++i){
        if(s[i]=='K'){
            for(int j=i-1;j>=0;--j){
                if(s[j]=='V')a[i]++;
                else{
                    if(s[j]=='K')a[i]+=a[j];
                    break;
                }
            }
        }
    } 

    if(s[n-1]=='K')b[n-1]=Inf;
    if(s[n-1]=='V'){
        int t=n-1;
        while(s[t]=='V')t--;
        if(s[t]=='K')b[t]=Inf;
    }

    for(int i=n-1;i>=0;--i){
        if(s[i]=='K'){
            for(int j=i+1;j<n;++j){
                if(s[j]=='V')b[i]++;
                else{
                    if(s[j]=='K')b[i]+=b[j];
                    else b[i]++;
                    break;
                }
            }
        }
    }
    
    int ans=0;
    for(int i=0;i<n;++i){
        if(s[i]=='K'){
            //cout<<i<<" "<<a[i]<<" "<<b[i]<<endl;
            ans+=min(a[i],b[i]);
        }
    }

    cout<<ans<<endl;

    return 0;
}