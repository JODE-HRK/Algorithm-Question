#include <iostream>
#include <stdio.h>
using namespace std;
const int maxn=1e6+10;

bool vis[maxn];
int main(){
    int n;
    cin>>n;
    long long int a;
    while(n--){
        scanf("%d",&a);
        if(a>=0&&a<maxn)vis[a]=1;
    }
    
    for(int i=0;i<maxn;++i){
        if(!vis[i]){
            cout<<i<<endl;
            break;
        }
    }

    return 0;
}