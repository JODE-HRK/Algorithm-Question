//
// Created by JODE on 2023-01-12.
//
#include <iostream>
#include <vector>
using namespace std;

vector<int> e[100005];
bool vis[100005];
int count[100005][30];
string str;

void dfs(int node){
    vis[node] = true;
    for(int i=0;i<e[node].size();++i){
        if (vis[e[node][i]])
            continue;
        dfs(e[node][i]);
        for (int j = 0; j < 26; ++j) {
            count[node][j] += count[e[node][i]][j];
        }
    }
    int id = str[node] - 'a';
    count[node][id] += 1;
}

vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 26; ++j) {
            count[i][j] = 0;
        }
        vis[i] = false;
    }
    for (int i = 0; i < edges.size(); ++i) {
        e[edges[i][0]].push_back(edges[i][1]);
        e[edges[i][1]].push_back(edges[i][0]);
    }
    str = labels;
    dfs(0);
    vector<int> Ans;
    for (int i = 0; i < labels.size(); ++i) {
        int id = labels[i] - 'a';
        Ans.push_back(count[i][id]);
    }
    return Ans;
}