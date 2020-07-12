#include <bits/stdc++.h>
#define ull unsigned long long 
using namespace std;
const int maxn=1e5+7;
const int mod=1e7+7;
const int base=2333333333;
int cnt=0,ans,nxt[maxn][21];
bool has[mod];
string A[maxn],B[maxn];
struct Node{
    string str;
    int dfn;
};
queue <Node> Q;
void getnxt(int nt[],int l,string str){
    fill(nt,nt+21,-1);
    int k=-1,i=0;
    while(i<l){
        if(k==-1 || str[k]==str[i])
            nt[++i]=++k;
        else k=nt[k];
    }
}
string replace(string str,int pos,int xp){
    str.replace(pos-1,A[xp].length(),B[xp]);
return str;
}
void kmp(string str,int tp[],int &tplen,int xp){
    int i=0,j=0,l=str.length(),len=A[xp].length();
    while(i<l){
        if(j==-1 || str[i]==A[xp][j])
            j++,i++;
        else    j=nxt[xp][j];
        if(j==len){
            tp[tplen++]=i-j+1;
            j=nxt[xp][j];
        }
    }
}
bool judge(string str){
    ull ha=0;
    for(int i=0;i<str.length();i++)
        ha=((ha*base)%mod+str[i]-'\0'+1)%mod;
    if(has[ha]==true)
        return 0;
    else{
        has[ha]=1;
        return 1;
    }
}
int bfs(){
    Node tmp;
    while (!Q.empty()){
        tmp=Q.front();
        Q.pop();
        if(tmp.str==B[0])
            return tmp.dfn;
        if(tmp.dfn>10)
            return 100;
        int tp[21],tplen;
        for(int i=1;i<cnt;i++){
            kmp(tmp.str,tp,tplen=0,i);
            for(int j=0;j<tplen;j++){
                string st=replace(tmp.str,tp[j],i);
                //cout<<st<<endl;
                if(judge(st))
                    Q.push((Node){st,tmp.dfn+1});
            }
        }
    }
return 100;
}
int main(){
    freopen(".in","r",stdin);
    // freopen(".out","w",stdout);

    while(cin>>A[cnt]>>B[cnt]){
        getnxt(nxt[cnt],A[cnt].length(),A[cnt]);
        cnt++;
    }
    Q.push((Node){A[0],0});
    ans=bfs();
    if(ans<=10)
        printf("%d",ans);
    else printf("NO ANSWER!");
return 0;
}