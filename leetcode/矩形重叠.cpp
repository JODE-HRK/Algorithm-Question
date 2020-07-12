#include <bits/stdc++.h>
#include <cstdio>
#include <cstdbool>
using namespace std;
int a[10], cnt = 0;
string str;
class Solution
{
public:
    bool judge()
    {
        int p1 = 0, p2 = 0;
        if (a[2] == a[6] || a[4] == a[8])
            p1 = 1;
        if (a[1] == a[5] || a[3] == a[7])
            p2 = 1;
        if (a[2] > a[6] && a[2] < a[8])
            p1 = 1;
        if (a[4] < a[8] && a[4] > a[6])
            p1 = 1;
        if (a[1] > a[5] && a[1] < a[7])
            p2 = 1;
        if (a[3] < a[7] && a[3] > a[5])
            p2 = 1;
        if ((a[1] < a[5] && a[3] > a[7]) || (a[5] < a[1] && a[7] > a[3]))
            p2 = 1;
        if ((a[2] < a[6] && a[4] > a[8]) || (a[6] < a[2] && a[8] > a[4]))
            p1 = 1;
        return p1 && p2;
    }
    bool isRectangleOverlap(vector<int> &rec1, vector<int> &rec2)
    {
        cnt = 0;
        for (auto x : rec1)
            a[++cnt] = x;
        for (auto x : rec2)
            a[++cnt] = x;
        return getans();
    }
    bool getans()
    {
        // getline(std::cin, str);
        // int sum = -1, p = 0;
        // for (int i = 0; i < str.length(); i++)
        // {
        //     char c = str[i];
        //     if (c == '[')
        //         p = 1;
        //     if (c == ']')
        //         p = 0;
        //     if (c >= '0' && c <= '9' && p)
        //     {
        //         if (sum < 0)
        //             sum = 0;
        //         sum = sum * 10 + c - '0';
        //     }
        //     else if (sum >= 0)
        //         a[++cnt] = sum, sum = -1;
        //     else
        //         sum = -1;
        // }
        if (judge()) //其实判断不重叠更容易
            return 1;
        else
            return 0;
    }
};