#include <bits/stdc++.h>
using namespace std;
int tree[14000][26],cnt,ans;
class Solution
{
public:
    void build(string s){
        int root =0;
        for(int i=0;i<s.length();i++){
            if(!tree[root][s[i]-'a'])
                tree[root][s[i]-'a']=++cnt;
            root = tree[root][s[i]-'a'];
        }
    }
    void dfs(int root,int len){//字典树的dfs遍历
        int p=0;
        for(int i=0;i<26;i++){
            if(tree[root][i]>0)
                dfs(tree[root][i],len+1),p=1;
        }
        if(!p)
            ans+=(len+1);
        return;
    }
    int minimumLengthEncoding(vector<string> &words)
    {
        memset(tree,0,sizeof(tree));
        cnt=ans=0;
        for(int i=0;i<words.size();i++){
            string s = words[i];
            reverse(s.begin(),s.end());
            build(s);
        }
        dfs(0,0);
        return ans;
    }
};