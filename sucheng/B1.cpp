#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;

map<string,int> mp;
int main(){
    int n;
    cin>>n;
    string s;
    for(int i=0;i<n;++i){
        cin>>s;
        mp[s]++;
    }
    int maxn=0;
    map<string,int>::iterator it;
    map<string,int>::iterator it1;
    for(it=mp.begin();it!=mp.end();it++){
        if(it->second>maxn){
            it1=it;
            maxn=it->second;
        }
    }

    if(maxn>(n-maxn))cout<<it1->first<<endl;
    else cout<<"NONE"<<endl;

    return 0;

}