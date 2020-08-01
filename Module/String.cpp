#include <bits/stdc++.h>
#define ll long long
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
/*Ekmp，字符串的扩展，计算S1中的每一个后缀子串与S2的最长公共前缀
nxt记录的是s2的后缀子串，与其本身的LCP（最长公共前缀）
ex记录的是s1中每一个位置往后的后缀子串与s2的LCP
*/
struct EKMP
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