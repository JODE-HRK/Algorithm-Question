#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=1000000;
class Splay{
    private:
        ll ch[maxn][2],f[maxn],size[maxn],cnt[maxn];
        ll sz,root;
        inline bool get(ll x){
            return ch[f[x]][1]==x;
        }
        inline void update(ll x){
            if (x){
                size[x]=cnt[x];
                if (ch[x][0]) size[x]+=size[ch[x][0]];
                if (ch[x][1]) size[x]+=size[ch[x][1]];
            }
        }
        inline void rotate(ll x){
            ll old=f[x],oldf=f[old],whichx=get(x);
            ch[old][whichx]=ch[x][whichx^1]; f[ch[old][whichx]]=old;
            ch[x][whichx^1]=old; f[old]=x;
            f[x]=oldf;
            if (oldf)
                ch[oldf][ch[oldf][1]==old]=x;
            update(old); update(x);
        }
        inline void splay(ll x){
            for (ll fa;fa=f[x];rotate(x))
              if (f[fa])
                rotate((get(x)==get(fa))?fa:x);
            root=x;
        }
    public:
        ll key[maxn];
        inline void clear(ll x){
            ch[x][0]=ch[x][1]=f[x]=size[x]=cnt[x]=key[x]=0;
        }
        void insert(ll x){
        if (root==0){sz++; ch[sz][0]=ch[sz][1]=f[sz]=0; root=sz; size[sz]=cnt[sz]=1; key[sz]=x; return;}
        ll now=root,fa=0;
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
    ll find(ll x){
        ll now=root,ans=0;
        while(1){
            if (x<key[now])
              now=ch[now][0];
            else{
                ans+=(ch[now][0]?size[ch[now][0]]:0);
                if (x==key[now]){
                    splay(now); return ans+1;
                }
                ans+=cnt[now];
                now=ch[now][1];
            }
        }
    }
    ll findx(ll x){
        ll now=root;
        while(1){
            if (ch[now][0]&&x<=size[ch[now][0]])
              now=ch[now][0];
            else{
                ll temp=(ch[now][0]?size[ch[now][0]]:0)+cnt[now];
                if (x<=temp) return key[now];
                x-=temp; now=ch[now][1];
            }
        }
    }
    ll pre(){
        ll now=ch[root][0];
        while (ch[now][1]) now=ch[now][1];
        return now;
    }
    ll next(){
        ll now=ch[root][1];
        while (ch[now][0]) now=ch[now][0];
        return now;
    }
    void del(ll x){
        ll whatever=find(x);
        if (cnt[root]>1){cnt[root]--; update(root); return;}
        if (!ch[root][0]&&!ch[root][1]) {clear(root); root=0; return;}
        if (!ch[root][0]){
            ll oldroot=root; root=ch[root][1]; f[root]=0; clear(oldroot); return;
        }
        else if (!ch[root][1]){
            ll oldroot=root; root=ch[root][0]; f[root]=0; clear(oldroot); return;
        }
        ll leftbig=pre(),oldroot=root;
        splay(leftbig);
        ch[root][1]=ch[oldroot][1];
        f[ch[oldroot][1]]=root;
        clear(oldroot);
        update(root);
    }
};
Splay F;
int main(){
    ll n,m,opt,x;
    scanf("%lld %lld",&n,&m);
    for(ll i=1;i<=n;i++)
    {
        scanf("%lld",&x);
        F.insert(x);
    }
    ll ans=0,lastans=0;
    for (ll i=1;i<=m;++i){
        scanf("%lld %lld",&opt,&x);
        x^=lastans;
        switch(opt){
            case 1: F.insert(x); break;
            case 2: F.del(x); break;
            case 3: lastans = F.find(x),ans ^= lastans; break;
            case 4: lastans = F.findx(x),ans ^= lastans; break;
            case 5: F.insert(x); lastans = F.key[F.pre()], ans ^= lastans; F.del(x); break;
            case 6: F.insert(x); lastans = F.key[F.next()], ans ^= lastans; F.del(x); break;
        }
    }
    printf("%lld",ans);
return 0;
}