#include <bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int maxn = 4e5+7;
int n;
int trie[maxn][26],tot=0;
int pos[maxn];
string str;
bool build(string ss){
    int l = ss.length(),root=0;
    for(int i=0;i<l;i++){
        int id = ss[i] - 'a';
        if(!trie[root][id])
            trie[root][id] = ++tot;
        root = trie[root][id];
    }
    if(pos[root])
        return 0;
    pos[root] = 1;
return 1;
}
int main(){
    int cnt=0;
    tot=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        cin >> str;
        if(str == "younik")
            break;
        cnt+=build(str);
    }
    printf("%d",cnt+1);
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