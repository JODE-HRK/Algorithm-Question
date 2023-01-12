//
// Created by JODE on 2023-01-11.
//
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> tree[100005];
    int son[100005];
    bool has[100005];
    bool vis[100005];

    int dfs(int node){
        int subtree = 0, allTime = 0;
        vis[node] = true;
        if (son[node] == 0){
            return false;
        }
        for (int i = 0; i <son[node]; ++i) {
            if (vis[tree[node][i]])
                continue;
            subtree = dfs(tree[node][i]);
            if (subtree > 0 || has[node])
                allTime += (subtree + 2);
        }
        return allTime;
    }

    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        tree->clear();
        for (int i = 0; i < n; ++i) {
            son[i] = 0;
            has[i] = hasApple[i];
            vis[i] = false;
        }
        for(int i = 0; i < edges.size(); i++){
            son[edges[i][0]] += 1;
            son[edges[i][1]] += 1;
            tree[edges[i][0]].push_back(edges[i][1]);
            tree[edges[i][1]].push_back(edges[i][0]);
        }
        return dfs(0);
    }
};