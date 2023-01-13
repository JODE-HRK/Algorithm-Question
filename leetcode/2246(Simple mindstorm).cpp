//
// Created by JODE on 2023-01-13.
//
#include <iostream>
#include <vector>
using namespace std;
vector<int> edge[100005];
string str;
int maxlen = 0;
// Remember it is no !adjacent same node!.
int dfs(int node){
    int longest = 0, secondLongest = 0, len;
    for (int i = 0; i < edge[node].size(); ++i) {
        int nxtNode = edge[node][i];
        len = dfs(nxtNode);
        if (str[node] == str[nxtNode])
            continue;
        if (len > longest){
            secondLongest = longest;
            longest = len;
        }
        else
            secondLongest = max(secondLongest, len);
    }
    maxlen = max(maxlen, longest + secondLongest + 1);
    return longest + 1;
}
int longestPath(vector<int>& parent, string s) {
    edge->clear();
    str = s;
    for (int i = 1; i < parent.size(); ++i) {
        int fa = parent[i];
        edge[fa].push_back(i);
    }
    dfs(0);
    return maxlen;
}