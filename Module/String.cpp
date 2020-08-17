#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ui unsigned int
using namespace std;
const int maxn = 1e7 + 7;
/*
kmp，返回s2在s1中的位置，或者计算s2在s1中出现的次数
*/
struct KMP
{
    queue<int> POS;
    string s1, s2;
    int nxt[maxn];
    void getnxt()
    {
        int l2 = s2.length();
        fill(nxt, nxt + 1 + l2, 0);
        nxt[0] = -1;
        for (int i = 0; i < l2; i++)
        {
            int k = nxt[i];
            while (k > 0 && s2[i] != s2[k])
                k = nxt[k];
            if (k == -1 || s2[k] == s2[i])
                nxt[i + 1] = k + 1;
        }
    }
    void kmp()
    {
        getnxt();
        int l1 = s1.length(), l2 = s2.length();
        int k = 0;
        for (int i = 0; i < l1; i++)
        {
            while (k && s2[k] != s1[i])
                k = nxt[k];
            if (k == -1 || s1[i] == s2[k])
                k++;
            if (k == l2)
            {
                POS.push(i - l2 + 1); //这个位置是从0开始算起的
                k = nxt[k];
            }
        }
    }
};
/*
使用kmp的nxt数组求字符串的循环节
*/
struct Circular_section//循环节
{
    string s;
    int nxt[maxn], len;
    void getnxt()
    {
        int len = s.length();
        fill(nxt, nxt + 1 + len, 0);
        nxt[0] = -1;
        for (int i = 0; i < len; i++)
        {
            int k = nxt[i];
            while (k > 0 && s[i] != s[k])
                k = nxt[k];
            if (k == -1 || s[k] == s[i])
                nxt[i + 1] = k + 1;
        }
    }
    int main()
    {
        cin >> s;
        len = s.length();
        getnxt();
        if (nxt[len] && len % (len - nxt[len]) == 0) //每次都是忘记了有个%==0的条件
        {
            printf("YES\n");
            printf("Len: %d\n", len - nxt[len]);           //循环节长度
            printf("Times: %d\n", len / (len - nxt[len])); //循环次数
        }
        else
            printf("NO\n");
        return 0;
    }
};
/*Ekmp，字符串的扩展，计算S1中的每一个后缀子串与S2的最长公共前缀
nxt记录的是s2的后缀子串，与其本身的LCP（最长公共前缀）
ex记录的是s1中每一个位置往后的后缀子串与s2的LCP
*/
struct EKMP//扩展KMP
{
    string s1, s2;
    int nxt[maxn], ex[maxn];
    void getEnxt()
    {
        int i = 0, j, po, l2 = s2.length();
        nxt[0] = l2;
        while (s2[i] == s2[i + 1] && i + 1 < l2)
            i++;
        nxt[1] = i, po = 1;
        for (i = 2; i < l2; i++)
        {
            if (nxt[i - po] + i < nxt[po] + po)
                nxt[i] = nxt[i - po];
            else
            {
                j = nxt[po] + po - i;
                if (j < 0)
                    j = 0;
                while (i + j < l2 && s2[j] == s2[i + j])
                    j++;
                nxt[i] = j;
                po = i;
            }
        }
    }
    void Ekmp()
    {
        getEnxt();
        int i = 0, j, po, l1 = s1.length(), l2 = s2.length();
        while (s1[i] == s2[i] && i < l1 && i < l2)
            i++;
        ex[0] = i, po = 0;
        for (i = 1; i < l1; i++)
        {
            if (nxt[i - po] + i < ex[po] + po)
                ex[i] = nxt[i - po];
            else
            {
                j = ex[po] + po - i;
                if (j < 0)
                    j = 0;
                while (i + j < l1 && j < l2 && s1[i + j] == s2[j])
                    j++;
                ex[i] = j, po = i;
            }
        }
    }
};
/*
Manache算法 查找一个字符串里面的最长回文子串
其实也把每个位置的最长回文子串求出来了
p数组就是每个位置的最长回文子串，在ss字符串中的位置
*/
struct MANACHER
{
    char s[maxn],
        ss[maxn << 1];
    int p[maxn << 1], maxlen, op;
    void manacher()
    {
        int id = 0, mx = 0;
        for (int i = 1; i < op; i++)
        {
            if (i < mx)
                p[i] = min(mx - i, p[2 * id - i]);
            else
                p[i] = 1;
            while (ss[i + p[i]] == ss[i - p[i]])
                p[i]++;
            if (mx < i + p[i])
                id = i, mx = i + p[i];
            maxlen = max(p[i], maxlen);
        }
    }
    void init()
    {
        maxlen = -1, op = 0;
        fill(p, p + 3 + strlen(s) * 2, 1);
    }
    void pre()
    {
        init();
        ss[0] += '$';
        int l = strlen(s);
        for (int i = 0; i < l; i++)
            ss[++op] = '#', ss[++op] = s[i];
        ss[++op] = '#', ss[++op] = '\0';
        manacher();
    }
};
/*
字符串的最小/大表示法
一个字符串循环排列，字典序最小/大的那个就是最小/大表示
循环同构
如： abdc 的最大表示法是 dcab
*/
struct Min_Expression //最小表示法
{
    int a[maxn], n; //n为长度，位置从0开始
    int getmin()
    {
        int i = 0, j = 1, k = 0, t;
        while (i < n && j < n && k < n)
        {
            t = a[(i + k) % n] - a[(j + k) % n]; //t表示当前两位置的大小
            if (!t)
                k++;
            else
            {
                if (t > 0) //大于改成小于就是最大表示法
                    i = i + k + 1;
                else
                    j = j + k + 1;
                if (i == j)
                    ++j;
                k = 0;
            }
        }
        return (i < j ? i : j); //返回最小表示法开始的位置
    }
};
/*
字符串哈希
现在我们经常使用map进行离散化等一些映射操作，但当对于字符串的时候，我们往往像将其用成hash
但是有时候会被时间卡住，
所以手动哈希还是得学一学的
手动哈希时间快，但是空间大
map则相反
*/
struct HASH
{
    map<string, int> Hash;
    int ans = 0, n;
    string s;
    void MapVersion()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            cin >> s;
            if (Hash.find(s) == Hash.end())
                Hash[s] = i, ans++; //统计不同单词的个数
        }
        printf("%d", ans);
    }
    const int mod = 998244353;
    const int base = 2333;
    void work()
    { //手动哈希
        priority_queue<int> Q;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            cin >> s;
            int hash = 0;
            for (int j = 0; j < s.length(); j++)
                hash = (hash * base + s[j]) % mod;
            Q.push(hash);
        }
        int last = -1;
        while (!Q.empty())
        {
            if (Q.top() != last)
                ans++;
            Q.pop();
        }
        printf("%d", ans);
    }
};
/*
字典树
多个字符串操作时常用、AC自动机前置知识
时间复杂度为O(nK)n个单词，k为单词的长度
查询一个单词是O(k)的时间复杂度
*/
struct Trie{
    int tot,trie[maxn][26];
    string s;
    void build(){
        int l = s.length(), root=0;
        for(int i=0;i<l;i++){ 
            int id = s[i]-'0';
            if (!trie[root][id])
                trie[root][id]=++tot;
            root = trie[root][id];
        }
        return;
    }
};
/*
AC自动机 多模匹配
通过建立fail串，获得各模板串之间的联系，
下例为 给你n个模板串，要你求有多少个模板串出现在了给出的字符串里面
对于要求从大文本中提取每个模式字符串出现的位置。
如果使用KMP算法，时间复杂度将达到O(LM+N)，
而使用AC自动机可以在O(N+M)时间复杂度内解决这一问题
该题是查询已有的字符串里面有几个在长串里面出现过
*/
struct AC_Automata{
    int tot, trie[maxn][26], n;
    int fail[maxn], pos[maxn];
    string s;
    void build(){
        int root=0, len=s.length();
        // ACinit();
        for(int i=0;i<len;i++){
            int id=s[i]-'a';
            if (!trie[root][id]) {
                trie[root][id]=++tot;
                for (int i=0;i<26;i++)
                    trie[tot][i]=0;//没有使用memset，时间复杂度进一步降低
                pos[tot]=0;
            }
            root=trie[root][id];
        }
        pos[root]++;
    }
    void getfail(){
        queue <int> Q;
        fail[0]=0;
        for (int i=0;i<26;i++) {
            if (trie[0][i])
            {
                fail[trie[0][i]]=0;
                Q.push(trie[0][i]);
            }
        }
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            for (int i=0;i<26;i++) {
                int son = trie[now][i];
                if(son)
                    fail[son] = trie[fail[now]][i],Q.push(son);
                else
                    trie[now][i] = trie[fail[now]][i];
            }
        }
    }
    inline int query(){
        int now =0, ans =0 ,l = s.length();
        for (int i=0;i<l;i++) {
            int id = s[i] - 'a';
            while (now && !trie[now][id])
                now = fail[now];
            now = trie[now][id];
            int tmp = now;
            while(tmp!=0){ 
                // printf("%d\n", now);
                ans+=pos[tmp];
                pos[tmp] = 0;
                tmp = fail[tmp];
            }
        }
        return ans;
    }
    int main(){
        int T;
        scanf("%d", &T);
        while(T--){
            tot=0;
            scanf("%d", &n);
            // ACinit();
            for (int i=0;i<26;i++)
                trie[0][i]=0;
            for(int i=1;i<=n;i++)
            {
                cin>>s;
                build();
            }
            getfail();
            cin>>s;
            printf("%d\n", query());
        }
        return 0;
    }
}; 
/*
离线的AC自动机，字符串的添加，贺询问穿插在中间，每次构造完成之后在建立fail指针时间复杂度会很高
所以就有了离线的AC自动机的做法
先把所有字符串添加进AC自动机，然后再倒序操作，遇到询问就用query查询，遇到字符串pos--
下例为牛客练习题 String（名字就叫String）
查询所有短串在长串里面的出现的次数之和
*/
struct AC_Automata_Offline{
    int tot, trie[maxn][26], n,k;
    int fail[maxn], pos[maxn];
    int last[maxn];//last数组是为了同一个串的多次查询
    struct PRO{
        int endpos,ans,type;
        string str;
    }pro[maxn];
    string s;
    int build(){
        int root=0, len=s.length();
        // ACinit();
        for(int i=0;i<len;i++){
            int id=s[i]-'a';
            if (!trie[root][id]) {
                trie[root][id]=++tot;
                for (int i=0;i<26;i++)
                    trie[tot][i]=0;
                pos[tot]=last[tot]=0;
            }
            root=trie[root][id];
        }
        pos[root]++;
    return root;//此处返回每一个字符串结尾的地方
    }
    void getfail(){
        queue <int> Q;
        fail[0]=0;
        for (int i=0;i<26;i++) {
            if (trie[0][i])
            {
                fail[trie[0][i]]=0;
                Q.push(trie[0][i]);
            }
        }
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            for (int i=0;i<26;i++){
                int son = trie[now][i];
                if(son)
                    fail[son] = trie[fail[now]][i],Q.push(son);
                else
                    trie[now][i] = trie[fail[now]][i];
                last[son] = (pos[fail[son]] ? fail[son] : last[fail[son]]);
            }
        }
    }
    inline int calc(int t){
        int tans=0;
        while(t){
            tans += pos[t];
            t = last[t];
        }
    return tans;
    }
    inline int query(string ss){
        int now =0, ans =0 ,l = ss.length();
        for (int i=0;i<l;i++) {
            int id = ss[i] - 'a';
            while (now && !trie[now][id])
                now = fail[now];
            now = trie[now][id];
            if(pos[now])
                ans += calc(now);
            else if(fail[now])
                ans += calc(fail[now]);
        }
        return ans;
    }
    int opt;
    int main(){
        int T;
        scanf("%d", &T);
        while(T--){
            tot=0;
            scanf("%d %d", &n,&k);
            // ACinit();
            for (int i=0;i<26;i++)
                trie[0][i]=0;
            for(int i=1;i<=n;i++)
            {
                cin>>s;
                build();
            }
            for(int i=1;i<=k;i++){
                scanf("%d",&opt);
                cin>>s;
                pro[i].type = opt;
                if(opt == 1)
                    pro[i].endpos = build();
                else
                    pro[i].str = s;
            }
            getfail();
            for(int i=k;i;i--){
                if(pro[i].type == 1)
                    --pos[pro[i].endpos];
                else
                    pro[i].ans = query(pro[i].str);
            }
            for(int i=1;i<=k;i++)
            if(pro[i].type==2)
                printf("%d\n",pro[i].ans);
        }
        return 0;
    } 
}; 