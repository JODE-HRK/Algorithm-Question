#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 7;

struct Definition
{
    int n, q, tot = 0;
    int a[maxn];
};
/*
主席树求区间不同树的个数
主席树每次修改和查询的时间复杂度都是O(logn)
*/
struct ChairmanTree_Different_numbers : Definition //区间不同数的个数
{                                                  //主席树支持在线做法
    //主席树空间很大，注意，并且有时候跑起来时间也很慢
    int cmtree[maxn], ls[maxn], rs[maxn], sum[maxn];
    unordered_map<int, int> pre; //相对于map来说，元素无序，但查找迅速O(1)
    void update(int l, int r, int node, int last, int p, int v)
    {
        ls[node] = ls[last], rs[node] = rs[last];
        sum[node] = sum[last] + v;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (mid >= p)
            update(l, mid, ls[node] = ++tot, ls[last], p, v);
        else
            update(mid + 1, r, rs[node] = ++tot, rs[last], p, v);
    }
    int cmtreequery(int l, int r, int node, int ql, int qr)
    {
        if (l >= ql && r <= qr)
            return sum[node];
        int mid = (l + r) >> 1;
        int ans = 0;
        if (mid >= ql)
            ans = cmtreequery(l, mid, ls[node], ql, qr);
        if (mid < qr)
            ans += cmtreequery(mid + 1, r, rs[node], ql, qr);
        return ans;
    }
    int main()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++)
        {
            if (pre[a[i]]) //如果这个数之前查过了，对上一个该数的位置进行-1更新
            {
                update(1, n, cmtree[i] = ++tot, cmtree[i - 1], pre[a[i]], -1);
                int now = ++tot;
                update(1, n, now, cmtree[i], i, 1);
                cmtree[i] = now;
            }
            else
                update(1, n, cmtree[i] = ++tot, cmtree[i - 1], i, 1);
            pre[a[i]] = i;
        }
        scanf("%d", &q);
        while (q--)
        {
            int l, r;
            scanf("%d %d", &l, &r);
            if (l > r)
                swap(l, r);
            printf("%d\n", cmtreequery(1, n, cmtree[r], l, r));
        }
        return 0;
    }
};

/*

*/
struct Lowbit_Different_numbers : Definition //区间不同数的个数
{                                            //树状数组只能离线查询
    int a[maxn], last[maxn], ans[maxn], val[maxn];
    struct Query
    {
        int l, r, id;
        bool operator<(const Query &x)
        {
            return r < x.r;
        }
    } que[maxn];
    int lowbit(int x)
    {
        return x & (-x);
    }
    void add(int pos, int c)
    {
        while (pos <= n)
        {
            val[pos] += c;
            pos += lowbit(pos);
        }
    }
    int getsum(int pos)
    {
        int res = 0;
        while (pos)
        {
            res += val[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
    int main()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        scanf("%d ", &q);
        for (int i = 1; i <= q; i++)
        {
            scanf("%d %d", &que[i].l, &que[i].r);
            que[i].id = i;
        }
        sort(que + 1, que + 1 + q);
        int pre = 0;
        for (int i = 1; i <= q; i++)
        {
            if (que[i].r > pre)
            {
                for (int j = pre + 1; j <= que[i].r; j++)
                {
                    if (last[a[j]])
                        add(last[a[j]], -1);
                    add(j, 1);
                    last[a[j]] = j; //此处如果数很大的话，可以离散化或者用map来记录上一次的位置
                    pre = que[i].r;
                }
            }
            ans[que[i].id] = getsum(que[i].r) - getsum(que[i].l - 1);
        }
        for (int i = 1; i <= q; i++)
            printf("%d\n", ans[i]);
        return 0;
    }
};

/*
分块算法，也称莫队算法，将数据分为sqrt(n)个部分，操作时对每个部分进行操作
时间复杂度 为O（n * sqrt(n)）
以牛客 名哥的完全平方数为例
*/
struct Block{
    int n,block,q;
    int a[maxn];
    int cnt[3000000];
    int zans[maxn];
    struct PRO{
        int l,r,id,sp;
        bool operator < (const PRO x){
            if(sp == x.sp)
                return r<x.r;
            return sp<x.sp;
        }
    }pro[maxn];
    inline int read(){
        char c = getchar();int x = 0,fh = 0;
        while(c < '0' || c > '9'){fh |= c == '-';c = getchar();}
        while(c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}
        return fh?-x:x;
    }
    int getnum(int x){
        int tmp = 1;
        // printf("%d\n",len);
        for(int i=2;i*i<=abs(x);i++){
            while(x%(i*i) == 0)
            x/=(i*i);
        }
        // printf("x:%d tmp:%d\n",x,tmp);
    return x/tmp;
    }
    int calc(int x){
        return x*(x-1)/2;
    }
    void work(int &ans,int val,int pos,int &cnt0){
        if(a[pos] == 0)
            cnt0+=val;
        else{
            ans -= calc(cnt[a[pos]+1000000]);
            cnt[a[pos]+1000000]+=val;
            ans += calc(cnt[a[pos]+1000000]);
        }
    }
    int main(){
        n =read();
        for(int i=1;i<=n;i++)
            a[i] = read(),a[i] = getnum(a[i]),cnt[a[i]]=0;
        // for(int i=1;i<=n;i++)
        //     printf("%d ",a[i]);
        // cout<<endl;
        block = sqrt(n);
        q = read();
        pro[0].l = pro[0].r =0;
        for(int i = 1;i<=q;i++){
            pro[i].l = read(),pro[i].r = read();
            pro[i].id = i;
            pro[i].sp = (pro[i].l-1)/block + 1;
        }
        sort(pro+1,pro+1+q);
    // printf("YES\n");
        int l=1,r=0,ans=0,cnt0=0;
        for(int i=1;i<=q;i++){
            while(l>pro[i].l)
                work(ans,1,--l,cnt0);
            while(r<pro[i].r)
                work(ans,1,++r,cnt0);
            while(l<pro[i].l)
                work(ans,-1,l++,cnt0);
            while(r>pro[i].r)
                work(ans,-1,r--,cnt0);
            zans[pro[i].id] = ans+cnt0*(r-l) - calc(cnt0);
            // lastcnt0 = cnt0;
        }
        for(int i=1;i<=q;i++)
            printf("%d\n",zans[i]);
        return 0;
    }
};