//求一个串的后缀子串与另一个串的最长公共前缀LCP的长度
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e6 + 7;
char str[maxn], tr[maxn];
int l, li, nxt[maxn], ex[maxn]; //nxt实际上就是自己对自己的ex数组，ex就代表每一个后缀串对模板串的最长公共前缀(LCP)的长度
void ekmpgetnxt()
{
    int a = 0, p = 0; //p代表最长匹配的长度，a代表开始匹配的位置
    nxt[0] = l;
    for (int i = 1; i < l; i++)
    {
        if (i >= p || i + nxt[i - a] >= p)
        {
            if (i >= p)
                p = i;
            while (p < l && str[p] == str[p - i])
                p++;
            nxt[i] = p - i, a = i;
        }
        else
            nxt[i] = nxt[i - a];
    }
    for (int i = 0; i < l; i++)
        printf("%d ", nxt[i]);
    cout << endl;
}
void ekmp()
{
    int i = 0, j, p0 = 0;
    li = strlen(tr); //母串的长度（不做getnxt的长度）
    while (i < li && i < l && str[i] == tr[i])
        i++; //注意都是i
    ex[0] = i;
    for (int i = 1; i < li; i++)
    {
        if (nxt[i - p0] + i < ex[p0] + p0)
            ex[i] = nxt[i - p0];
        else
        {
            j = ex[p0] + p0 - i;
            if (j < 0)
                j = 0;
            while (i + j < li && j < l && tr[i + j] == str[j])
                j++;
            ex[i] = j;
            p0 = i;
        }
    }
    for (int i = 0; i < li; i++)
        printf("%d ", ex[i]); //输出母串的ex数组（即每一个后缀串对母串的最长公共前缀）
    cout << endl;
}
int main()
{
    scanf("%s", tr);
    scanf("%s", str);
    l = strlen(str);
    ekmpgetnxt();
    ekmp();
    return 0;
}
