#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e6 + 7;
int n;
int pos[maxn];
stack<int> st;
string s;
struct SAM
{
    int last, tot, trie[maxn << 1][26], fa[maxn << 1], slen[maxn << 1], num[maxn << 1];
    //trie树 + fa[x]（endpos集合为x的父亲节点）+ slen[x] （x位置所属集合中字符串的最大长度） + num[x]（出现次数为x的字符串位置）
    void init()
    {
        last = tot = 1;                      //第一个位置为空，记为0号节点
        memset(trie[1], 0, sizeof(trie[1])); //初始化
        fa[1] = slen[1] = num[1] = 0;
    }
    inline int buildnode()
    { //新建一个节点
        tot++;
        memset(trie[tot], 0, sizeof(trie[tot]));
        fa[tot] = slen[tot] = num[tot] = 0;
        return tot;
    }
    void add(int c)
    {
        int p = last, np = buildnode();
        last = np;
        slen[np] = slen[p] + 1;
        while (p && !trie[p][c])
        {
            trie[p][c] = np;
            p = fa[p];
        }
        if (!p)
            fa[np] = 1;
        else
        {
            int q = trie[p][c];
            if (slen[q] == slen[p] + 1)
                fa[np] = q;
            else
            {
                int nq = buildnode();
                memcpy(trie[nq], trie[q], sizeof(trie[q]));
                fa[nq] = fa[q];
                num[nq] = num[q];
                slen[nq] = slen[p] + 1;
                fa[np] = fa[q] = nq;
                while (trie[p][c] == q)
                {
                    trie[p][c] = nq;
                    p = fa[p];
                }
            }
        }
    }
} sam;
int main()
{
    cin >> s;
    sam.init(); //sam数组，后缀自动机初始化
    int len = s.length();
    pos[len] = 1;
    while (!st.empty())
        st.pop();
    st.push(len);
    for (int i = len - 1; ~i; i--) //后缀当然是从后往前扫啦
    {
        while (st.size() > 1 && s[st.top()] < s[i])
            st.pop(); //单调栈维护后面第一个值比它大的位置
        sam.last = pos[st.top()];
        for (int j = i; j < st.top(); j++) //把一直到那个位置之前的子串加进去
            sam.add(s[i] - 'a');
        st.push(i);        //当前位置加入单调栈
        pos[i] = sam.last; //pos记录当前位置后面第一个比它大的位置
    }
    ll ans = 0;
    for (int i = 2; i <= sam.tot; i++) //从2开始因为0号节点记为1
        ans += 1ll * (sam.slen[i] - sam.slen[sam.fa[i]]);
    printf("%lld", ans);
    return 0;
}
/*
后缀自动机修改版
*/