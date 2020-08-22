#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+7;
class Splay{
    private:
        int ch[maxn][2],f[maxn],size[maxn],cnt[maxn];
        int sz,root;
        inline bool get(int x){
            return ch[f[x]][1]==x;
        }
        inline void update(int x){
            if (x){
                size[x]=cnt[x];
                if (ch[x][0]) size[x]+=size[ch[x][0]];
                if (ch[x][1]) size[x]+=size[ch[x][1]];
            }
        }
        inline void rotate(int x){
            int old=f[x],oldf=f[old],whichx=get(x);
            ch[old][whichx]=ch[x][whichx^1]; f[ch[old][whichx]]=old;
            ch[x][whichx^1]=old; f[old]=x;
            f[x]=oldf;
            if (oldf)
                ch[oldf][ch[oldf][1]==old]=x;
            update(old); update(x);
        }
        inline void splay(int x){
            for (int fa;fa=f[x];rotate(x))
              if (f[fa])
                rotate((get(x)==get(fa))?fa:x);
            root=x;
        }
    public:
        int key[maxn];
        inline void clear(int x){
            ch[x][0]=ch[x][1]=f[x]=size[x]=cnt[x]=key[x]=0;
        }
        void insert(int x){
        if (root==0){sz++; ch[sz][0]=ch[sz][1]=f[sz]=0; root=sz; size[sz]=cnt[sz]=1; key[sz]=x; return;}
        int now=root,fa=0;
        while(1){
            if (x==key[now]){
                cnt[now]++; update(now); update(fa); splay(now); break;
            }
            fa=now;
            now=ch[now][key[now]<x];
            if (now==0){
                sz++;
                ch[sz][0]=ch[sz][1]=0;
                f[sz]=fa;
                size[sz]=cnt[sz]=1;
                ch[fa][key[fa]<x]=sz;
                key[sz]=x;
                update(fa);
                splay(sz);
                break;
            }
        }
    }
    int find(int x){
        int now=root,ans=0;
        while(1){
            if(now==0)
                return 1;
            if (x<key[now])
              now=ch[now][0];
            else{
                ans+=(ch[now][0]?size[ch[now][0]]:0);
                if (x==key[now]){
                    splay(now); 
                    return ans+1;
                }
                ans+=cnt[now];
                now=ch[now][1];
            }
        }
    }
    int findx(int x){
        int now=root;
        while(1){
            if (ch[now][0]&&x<=size[ch[now][0]])
              now=ch[now][0];
            else{
                int temp=(ch[now][0]?size[ch[now][0]]:0)+cnt[now];
                if (x<=temp) return key[now];
                x-=temp; now=ch[now][1];
            }
        }
    }
    int pre(){
        int now=ch[root][0];
        while (ch[now][1]) now=ch[now][1];
        return now;
    }
    int next(){
        int now=ch[root][1];
        while (ch[now][0]) now=ch[now][0];
        return now;
    }
    void del(int x){
        int whatever=find(x);
        if (cnt[root]>1){cnt[root]--; update(root); return;}
        if (!ch[root][0]&&!ch[root][1]) {clear(root); root=0; return;}
        if (!ch[root][0]){
            int oldroot=root; root=ch[root][1]; f[root]=0; clear(oldroot); return;
        }
        else if (!ch[root][1]){
            int oldroot=root; root=ch[root][0]; f[root]=0; clear(oldroot); return;
        }
        int leftbig=pre(),oldroot=root;
        splay(leftbig);
        ch[root][1]=ch[oldroot][1];
        f[ch[oldroot][1]]=root;
        clear(oldroot);
        update(root);
    }
};
Splay F;
int main(){
    int n,opt,x,m;
    int zans=0;
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        F.insert(x);
    }
    int lastans=0;
    for (int i=1;i<=m;++i){
        scanf("%d %d",&opt,&x);
        x = x^lastans;
        switch(opt){
            case 1: F.insert(x); break;
            case 2: F.del(x); break;
            case 3: lastans = F.find(x), zans^=lastans; break;
            case 4: lastans = F.findx(x), zans^=lastans; break;
            case 5: F.insert(x); lastans = F.key[F.pre()], zans ^= lastans; F.del(x); break;
            case 6: F.insert(x); lastans = F.key[F.next()], zans ^= lastans; F.del(x); break;
        }
    }
    printf("%d",zans);
return 0;
}
