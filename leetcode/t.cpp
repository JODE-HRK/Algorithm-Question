#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool judge(string s1, string s2)
    {
        if (s1.length() != s2.length())
            return 0;
        int a[26], b[26], cnt1 = 0, cnt2 = 0;
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        vector<int> A, B;
        A.clear(), B.clear();
        for (int i = 0; i < s1.length(); i++)
        {
            int aa = s1[i] - 'a', bb = s2[i] - 'a';
            if (!a[aa])
                a[aa] = ++cnt1;
            A.push_back(a[aa]);
            if (!b[bb])
                b[bb] = ++cnt2;
            B.push_back(b[bb]);
        }
        for (int i = 0; i < A.size(); i++)
        {
            if (A[i] != B[i])
                return 0;
        }
        return 1;
    }
    vector<string> findAndReplacePattern(vector<string> &words, string pattern)
    {
        vector<string> ans;
        for(auto v:words){
            if(judge(v,pattern))
                ans.push_back(v);
        }
        return ans;
    }
};