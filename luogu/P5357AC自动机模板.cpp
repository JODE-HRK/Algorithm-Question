#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e6 + 7, T = 2e5 + 7;
int n, tot = 0;
int trie[T][26], pos[T], fail[T], sz[T], head[T], to[T], nxt[T], cnt = 0;
char str[maxn];
int build()
{
    int root = 0;
    for (int i = 0; str[i]; i++)
    {
        int id = str[i] - 'a';
        if (!trie[root][id])
            trie[root][id] = ++tot;
        root = trie[root][id];
    }
    return root;
}
void build_fail()
{
    queue<int> Q;
    for (int i = 0; i < 26; i++)
        if (trie[0][i])
            Q.push(trie[0][i]), fail[trie[0][i]] = 0; // 第一层，所有的fail都是指向root=0的
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < 26; i++)
        {
            if (trie[u][i]) //如果这个儿子存在
                fail[trie[u][i]] = trie[fail[u]][i], Q.push(trie[u][i]);
            //那么这个儿子就指向父亲的fail指针的与其相同的儿子
            else //如果这个儿子不存在
                trie[u][i] = trie[fail[u]][i];
            //那么这个儿子就是其父亲节点fail指针的那个儿子（不用指针了，直接将下面空节点赋值）
        }
    }
}

void increase(int u, int v)
{
    nxt[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
}

void dfs(int u)
{
    int v;
    for (int i = head[u]; i; i = nxt[i])
    {
        v = to[i];
        dfs(v);
        sz[u] += sz[v];
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", str);
        pos[i] = build(); //字典树建立
    }

    build_fail(); //建立fail指针

    scanf("%s", str);

    int u = 0;
    for (int i = 0; str[i]; i++)
    {
        int id = str[i] - 'a';
        u = trie[u][id];
        ++sz[u];
    } //记录有哪些点是在str上面的

    for (int i = 1; i <= tot; i++)
        increase(fail[i], i); //反向fail指针建树

    dfs(0); //fail树上、查询，因为只有sz>0的节点，才是模板串的节点，也就是说，在fail树上，
            //每个节点的子树里有多少个sz>0,该节点就有多少次出现在模板串上

    for (int i = 1; i <= n; i++)
        printf("%d\n", sz[pos[i]]);
    return 0;
}
//给你n个串，要你求这n个串在模板串s中各出现了多少次